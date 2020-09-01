#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "component_heap.h"
#include "madd_base.h"
#include "maybe.h"
#include "status.h"
#include "system.h"

// template <typename... Types>
// struct SystemInfo {
//   std::unique_ptr<System> system;
//   ComponentHeap::TypeSet<Types...> typeset;
// };
// template <typename... ComponentSystems>
class Madd : public MaddBase {
  auto processSystems() -> Status;
  auto processUpdates() -> Status;

 public:
  ~Madd() = default;
  auto GameTick() -> Status;

  // Move, deleted
  Madd(Madd&& other) noexcept = delete;
  auto operator=(Madd&& other) noexcept -> Madd& = delete;

  // Copy, deleted
  Madd(const Madd&) = delete;
  auto operator=(const Madd&) -> Madd& = delete;
};

auto Madd::GameTick() -> Status {
  auto status = processSystems();
  if (status.Ok()) {
    return status;
  }
  return processUpdates();
}

auto Madd::processSystems() -> Status {
  // Status status;
  // for (auto& [system, typeSet] : systems) {
  //   status = system->Process(typeSet);
  //   if (!status.Ok()) {
  //     return status;
  //   }
  // }
  return Status::OK_RESPONSE;
};

auto Madd::processUpdates() -> Status {
  return Status::OK_RESPONSE;
};
