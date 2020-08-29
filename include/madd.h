#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "component_heap.h"
#include "madd_base.h"
#include "maybe.h"
#include "status.h"
#include "system.h"

template <typename... Types>
struct SystemInfo {
  std::unique_ptr<System> system;
  ComponentHeap::TypeSet<Types...> typeset;
};

template <template <System* system, typename... Types> class... SystemInfo>
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

template <template <System* system, typename... Types> class... SystemInfo>
auto Madd<SystemInfo...>::GameTick() -> Status {
  auto status = processSystems();
  if (status.Ok()) {
    return status;
  }
  return processUpdates();
}

template <template <System* system, typename... Types> class... SystemInfo>
auto Madd<SystemInfo...>::processSystems() -> Status {
  // Status status;
  // for (auto& [system, typeSet] : systems) {
  //   status = system->Process(typeSet);
  //   if (!status.Ok()) {
  //     return status;
  //   }
  // }
  return Status::OK_RESPONSE;
};

template <template <System* system, typename... Types> class... SystemInfo>
auto Madd<SystemInfo...>::processUpdates() -> Status {
  return Status::OK_RESPONSE;
};
