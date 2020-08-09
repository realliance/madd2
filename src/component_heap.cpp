#include <unordered_map>
#include <utility>
#include "component_heap.h"

void Heap::erase(Entity entity, ComponentType componentType){
  auto itr = componentTypeMap.find(componentType);
  if(itr != std::end(componentTypeMap)){
    itr->second.erase(entity);
  }
}

void Heap::clear(){
  componentTypeMap.clear();
}

auto Heap::data() -> ComponentTypeMap* { return &componentTypeMap; }

auto Heap::begin(const std::vector<ComponentType>& componentTypes)
  -> Heap::iterator {
  return iterator(&componentTypeMap, componentTypes,
                  /*moveToEnd=*/false);
}

auto Heap::end(const std::vector<ComponentType>& componentTypes)
  -> Heap::iterator {
  return iterator(&componentTypeMap, componentTypes,
                  /*moveToEnd=*/true);
}
