#pragma once
#include "changeset.h"
#include "maybe.h"

class ComponentHeap;
class System {
 public:
  virtual ~System() = 0;

  virtual Maybe<std::vector<ChangeSet>> Process(const ComponentHeap* heap) = 0;
};
