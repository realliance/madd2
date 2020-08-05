#include <unordered_map>
#include <utility>
#include "component_heap.h"
#include "heap_entry.h"

ComponentTypeMap::iterator Heap::getComponentMap(ComponentType componentType){
  ComponentTypeMap::iterator itr = componentTypeMap.find(componentType);
  if(itr == std::end(componentTypeMap)){
    componentTypeMap[componentType] = {};
    itr = componentTypeMap.find(componentType);
  }
  return itr;
}

void Heap::insert(Entity entity, ComponentType componentType, HeapEntry heapEntry){
  componentTypeMap[componentType][entity] = heapEntry;
}

void Heap::erase(Entity entity, ComponentType componentType){
  getComponentMap(componentType)->second.erase(entity);
}

void Heap::clear(){
  componentTypeMap.clear();
}

ComponentMap::iterator Heap::find(Entity entity, ComponentType componentType){
  return getComponentMap(componentType)->second.find(entity);
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

ComponentMap::iterator Heap::begin(ComponentType componentType){
  return getComponentMap(componentType)->second.begin();
}

ComponentMap::iterator Heap::end(ComponentType componentType){
  return getComponentMap(componentType)->second.end();
}
