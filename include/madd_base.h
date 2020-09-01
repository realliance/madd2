#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "component_heap.h"
#include "maybe.h"
#include "status.h"
#include "system.h"

class MaddBase {
  ComponentHeap componentHeap;
  Entity nextEntityId = ReservedEntity::FIRST_VALID_ENTITY;

  template <class T>
  auto addComponent(Entity entity, T* component) -> Status;
  template <class T>
  auto removeComponent(Entity entity) -> Status;

 public:
  ~MaddBase() = default;

  template <class... Types>
  auto CreateEntity(Types... components) -> Maybe<Entity>;
  template <typename T, typename... Types>
  auto AddComponents(Entity entity, T* component, Types*... components)
    -> Status;
  template <typename T, typename... Types>
  auto RemoveComponents(Entity entity, T* component, Types*... components)
    -> Status;

  // Move
  MaddBase(MaddBase&& other) noexcept = delete;
  auto operator=(MaddBase&& other) noexcept -> MaddBase& = delete;

  // Copy, deleted
  MaddBase(const MaddBase&) = delete;
  auto operator=(const MaddBase&) -> MaddBase& = delete;
};

template <class... Types>
auto MaddBase::CreateEntity(Types... components) -> Maybe<Entity> {
  Entity entity = nextEntityId++;
  if (nextEntityId == ReservedEntity::LAST_ENTITY) {
    return Status{StatusCode::GENERAL_MADD_FAILURE,
                  "WARNING: Max Entity Id Reached!", false};
  }
  auto status = addComponents(entity, components...);
  if (status) {
    return entity;
  }
  nextEntityId--;
  status.details =
    "Failed to create Entity: an error occured during adding components: " +
    status.details;
  auto removeStatus = RemoveComponents(entity, components...);
  if (removeStatus) {
    return status;
  }
  std::cerr << "An additional error occured attempting to clean up component "
               "resources: ";
  std::cerr << removeStatus;
  throw(removeStatus);
}

template <typename T, typename... Types>
auto MaddBase::RemoveComponents(Entity entity, T* component,
                                Types*... components) -> Status {
  return RemoveComponents<Types...>(entity, components...)
           ? removeComponent(entity, component)
           : false;
}

template <typename T, typename... Types>
auto MaddBase::AddComponents(Entity entity, T* component, Types*... components)
  -> Status {
  return AddComponents(entity, components...) ? addComponent(entity, component)
                                              : false;
}

template <class T>
auto MaddBase::removeComponent(Entity entity) -> Status {
  return componentHeap.erase<T>(entity);
}

template <class T>
auto MaddBase::addComponent(Entity entity, T* component) -> Status {
  return componentHeap.insert<T>(entity, component);
}
