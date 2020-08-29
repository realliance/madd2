#include "component_heap.h"

void ComponentHeap::clear() { componentTypeMap.clear(); }
auto ComponentHeap::data() -> ComponentTypeMap* { return &componentTypeMap; }
