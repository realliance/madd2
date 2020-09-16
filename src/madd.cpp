#include "madd.h"

#include "changeset.h"
#include "maybe.h"

auto Madd::GameTick() -> Status {
  auto status = processSystems();
  if (status.Ok()) {
    return status;
  }
  return processUpdates();
}

auto Madd::processSystems() -> Status {
  Maybe<std::vector<ChangeSet>> maybeChangesets;
  for (auto& system : systems) {
    maybeChangesets = system.Process(&componentHeap);
    if (!maybeChangesets.Ok()) {
      return maybeChangesets.GetStatus();
    }
  }
  return Status::OK_RESPONSE;
};

auto Madd::processUpdates() -> Status {
  return Status::OK_RESPONSE;
};
