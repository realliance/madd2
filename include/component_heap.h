#pragma once
#include <iosfwd>
#include <iterator>
#include <map>
#include <vector>
#include "heap_entry.h"
#include "types.h"

class Heap{
  ComponentTypeMap componentTypeMap;
  ComponentTypeMap::iterator getComponentMap(ComponentType componentType);
public:
  void insert(Entity entity, ComponentType componentType, HeapEntry heapEntry);
  void erase(Entity entity, ComponentType componentType);
  ComponentMap::iterator find(Entity entity, ComponentType componentType);
  void clear();
  ComponentTypeMap* data();

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
    std::vector<HeapEntry> operator*() const;
    // iterator traits
    using difference_type = std::ptrdiff_t;
    using value_type = std::vector<HeapEntry>;
    using pointer = const std::vector<HeapEntry>*;
    using reference = const std::vector<HeapEntry>&;
    using iterator_category = std::input_iterator_tag;
  };


  iterator begin(std::vector<ComponentType> componentTypes);
  iterator end(std::vector<ComponentType> componentTypes);
  ComponentMap::iterator begin(ComponentType componentType);
  ComponentMap::iterator end(ComponentType componentType);
};

std::ostream& operator<<(std::ostream& os, const Heap::iterator& iterator);
