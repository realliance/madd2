#pragma once

#include <any>
#include <vector>
#include "entity.h"

class ChangeSet {
  Entity entity;
  std::vector<bool> changedMembers;
  std::any change;
};
