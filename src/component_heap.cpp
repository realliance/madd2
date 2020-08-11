#include "component_heap.h"

void Heap::clear() { componentTypeMap.clear(); }
auto Heap::data() -> ComponentTypeMap* { return &componentTypeMap; }
