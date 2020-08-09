#pragma once
#include <iosfwd>
#include <iterator>
#include <map>
#include <unordered_map>
#include <vector>

#include "heap_entry.h"
#include "types.h"

class Heap {
  ComponentTypeMap componentTypeMap;
  ComponentId nextComponentId = 0;

 public:
  class iterator {
    friend Heap;
    friend auto operator<<(std::ostream& os, const Heap::iterator& iterator)
      -> std::ostream&;
    std::vector<ComponentType> componentTypes;
    std::vector<ComponentMap::iterator> componentIterators;
    std::vector<ComponentMap*> componentMaps;
    bool atEnd;
    iterator(ComponentTypeMap* componentTypeMap,
             const std::vector<ComponentType>& componentTypes,
             bool moveToEnd = false);
    static auto compareComponentIterators(const ComponentMap::iterator& lhs,
                                          const ComponentMap::iterator& rhs)
      -> bool;

   public:
    auto operator++() -> iterator&;
    auto operator++(int) -> iterator;
    auto operator--() -> iterator&;
    auto operator--(int) -> iterator;
    auto operator==(const iterator& other) const -> bool;
    auto operator!=(const iterator& other) const -> bool;
    auto operator*() const -> std::vector<HeapEntry*>;
    // iterator traits
    using difference_type = std::ptrdiff_t;
    using value_type = std::vector<HeapEntry>;
    using pointer = const std::vector<HeapEntry>*;
    using reference = const std::vector<HeapEntry>&;
    using iterator_category = std::input_iterator_tag;
  };

  template <typename T>
  void insert(Entity entity, ComponentType componentType, T* heapEntry);
  void erase(Entity entity, ComponentType componentType);
  void clear();
  auto data() -> ComponentTypeMap*;
  auto begin(const std::vector<ComponentType>& componentTypes) -> iterator;
  auto end(const std::vector<ComponentType>& componentTypes) -> iterator;
};

auto operator<<(std::ostream& os, const Heap::iterator& iterator)
  -> std::ostream&;

template <typename T>
void Heap::insert(Entity entity, ComponentType componentType, T* heapEntry) {
  componentTypeMap[componentType][entity] =
    HeapEntry(heapEntry, nextComponentId++);
}
