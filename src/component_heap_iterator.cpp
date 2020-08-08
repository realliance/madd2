#include <ext/alloc_traits.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>
#include "component_heap.h"
#include "types.h"
class HeapEntry;

Heap::iterator::iterator(ComponentTypeMap* componentTypeMap, std::vector<ComponentType> componentTypes, bool moveToEnd)
: componentTypes(componentTypes), atEnd(moveToEnd){
  if(atEnd) return;
  if(componentTypeMap->empty()){
    atEnd = true;
    return;
  }

  Entity e = 0;
  bool first = true;
  bool match = true;
  for(const auto& type : componentTypes){
    ComponentTypeMap::iterator componentTypeMapItr = componentTypeMap->find(type);
    if(componentTypeMapItr == componentTypeMap->end()){
      atEnd = true;
      return;
    }
    componentIterators.push_back(componentTypeMapItr->second.begin());
    componentMaps.push_back(&(componentTypeMapItr->second));
    if(componentIterators.front() == std::end(*componentMaps.front())){
      atEnd = true;
      return;
    }
    if(match && e != (componentIterators.front())->first){
      if(first){
        e = (componentIterators.front())->first;
      }else{
        match = false;
      }
    } 
  }
  if(match) return;
  operator++(); return;
}

Heap::iterator& Heap::iterator::operator++(){
  std::vector<ComponentMap*>::iterator componentMapsItr = componentMaps.begin();
  for(auto& componentIterator : componentIterators){
    componentIterator++;
    if((*componentMapsItr++)->end() == componentIterator){
      atEnd = true;
      return *this;
    }
  }
  Entity e = componentIterators.front()->first;
  while(
      !(std::all_of(std::begin(componentIterators), std::end(componentIterators),
      [e](const ComponentMap::iterator& ci){
        return ci->first == e;
      }))
    ){
      std::vector<ComponentMap::iterator>::iterator minEntityIteratorItr = std::min_element(
        std::begin(componentIterators), std::end(componentIterators), compareComponentIterators
      );
      (*minEntityIteratorItr)++;
      ComponentMap::iterator minEntityIteratorEnd = std::end(*componentMaps.at(
        std::distance(std::begin(componentIterators),minEntityIteratorItr)
      ));
      if(*minEntityIteratorItr == minEntityIteratorEnd){
        atEnd = true;
        return *this;
      }
  };
  return *this;
}

Heap::iterator Heap::iterator::operator++(int){
  iterator tmp(*this);
  operator++();
  return tmp;
}


bool Heap::iterator::compareComponentIterators(const ComponentMap::iterator& lhs, const ComponentMap::iterator& rhs){
  return lhs->first < rhs->first;
}


bool Heap::iterator::operator==(const iterator& other) const{
  if(atEnd != other.atEnd){
     return false;
  }
  if(componentTypes.size() != other.componentTypes.size()){
    return false;
  }
  if(!std::equal(componentTypes.begin(),componentTypes.end(),other.componentTypes.begin())){
    return false;
  }
  if(atEnd){
    return true;
  } 
  return other.componentIterators.front() == componentIterators.front();
}

bool Heap::iterator::operator!=(const iterator& other) const{
  return !operator==(other);
}

std::vector<HeapEntry*> Heap::iterator::operator*() const{
  std::vector<HeapEntry*> entries;
  for(auto& componentIterator: componentIterators){
    entries.push_back(&componentIterator->second);
  }
  return entries;
}

std::ostream& operator<<(std::ostream& os, const Heap::iterator& iterator){
  os << "{ " << "End: " << iterator.atEnd; 
  os << ", componentIterators positions: [";
  for(const auto& componentIterator: iterator.componentIterators){
    os << &componentIterator->second << ", ";
  }
  os << "], componentMaps: [";
  for(const auto& componentMap: iterator.componentMaps){
    os << "Size: " << componentMap->size() << ", ";
  }
  os << "]}";
  return os;
}
