#pragma once
#include <iosfwd>
#include <iterator>
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>
#include "types.h"
#include "heap_entry.h"

class Heap{
  ComponentTypeMap componentTypeMap;
  ComponentId nextComponentId = 0;
public:

  class iterator {
    friend Heap;
    friend std::ostream& operator<<(std::ostream& os, const Heap::iterator& iterator);
    std::vector<ComponentType> componentTypes;
    std::vector<ComponentMap::iterator> componentIterators;
    std::vector<ComponentMap*> componentMaps;
    bool atEnd;
    iterator(ComponentTypeMap* componentTypeMap, std::vector<ComponentType> componentTypes, bool moveToEnd=false);
    static bool compareComponentIterators(const ComponentMap::iterator& lhs, const ComponentMap::iterator& rhs);
  public:
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    std::vector<HeapEntry*> operator*() const;
    // iterator traits
    using difference_type = std::ptrdiff_t;
    using value_type = std::vector<HeapEntry>;
    using pointer = const std::vector<HeapEntry>*;
    using reference = const std::vector<HeapEntry>&;
    using iterator_category = std::input_iterator_tag;
  };

  template<typename T>
  void insert(Entity entity, ComponentType componentType, T* heapEntry);
  void erase(Entity entity, ComponentType componentType);
  void clear();
  ComponentTypeMap* data();
  iterator begin(std::vector<ComponentType> componentTypes);
  iterator end(std::vector<ComponentType> componentTypes);
};

std::ostream& operator<<(std::ostream& os, const Heap::iterator& iterator);

template<typename T>
void Heap::insert(Entity entity, ComponentType componentType, T* heapEntry){
  componentTypeMap[componentType][entity] = std::move(HeapEntry(heapEntry,nextComponentId++));
}
