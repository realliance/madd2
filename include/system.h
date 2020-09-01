#pragma once
#include <type_traits>

#include "changeset.h"
#include "component_heap.h"

template <typename ComponentSystem>
class System {
  template <typename... Types>
  auto Process(const ComponentHeap::TypeSet<Types...>& typeset) {
    return static_cast<ComponentSystem*>(this)->ProcessComponents(typeset);
  }
};
