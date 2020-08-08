#include <unordered_map>
#include <utility>
#include "component_heap.h"

void Heap::erase(Entity entity, ComponentType componentType){
  ComponentTypeMap::iterator itr = componentTypeMap.find(componentType);
  if(itr != std::end(componentTypeMap)){
    itr->second.erase(entity);
  }
}

void Heap::clear(){
  componentTypeMap.clear();
}

ComponentTypeMap* Heap::data(){
  return &componentTypeMap;
}

Heap::iterator Heap::begin(std::vector<ComponentType> componentTypes) {
  return iterator(&componentTypeMap,componentTypes, false);
}

Heap::iterator Heap::end(std::vector<ComponentType> componentTypes) {
  return iterator(&componentTypeMap,componentTypes, true);
}

