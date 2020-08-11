#pragma once
#include <iosfwd>
#include <iterator>
#include <map>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "heap_entry.h"
#include "types.h"

using ComponentMap = std::map<Entity, HeapEntry>;
using ComponentTypeMap = std::unordered_map<std::type_index, ComponentMap>;

class Heap {
  ComponentTypeMap componentTypeMap;
  ComponentId nextComponentId = 0;

 public:
  class iterator {
    friend Heap;
    friend auto operator<<(std::ostream& os, const Heap::iterator& iterator)
      -> std::ostream&;
    std::vector<std::type_index> componentTypes;
    std::vector<ComponentMap::iterator> componentIterators;
    std::vector<ComponentMap*> componentMaps;
    bool atEnd;
    iterator(ComponentTypeMap* componentTypeMap,
             const std::vector<std::type_index>& componentTypes,
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
    using pointer = const std::vector<HeapEntry*>;
    using reference = const std::vector<HeapEntry&>;
    using iterator_category = std::input_iterator_tag;
  };

  template <typename T>
  void insert(Entity entity, T* heapEntry);
  template <typename T>
  void erase(Entity entity);
  void clear();
  auto data() -> ComponentTypeMap*;
  template <class... Types>
  auto begin() -> iterator;
  template <class... Types>
  auto end() -> iterator;
};

auto operator<<(std::ostream& os, const Heap::iterator& iterator)
  -> std::ostream&;

template <typename T>
void Heap::insert(Entity entity, T* heapEntry) {
  componentTypeMap[std::type_index(typeid(T))][entity] =
    HeapEntry(heapEntry, nextComponentId++);
}

template <typename T>
void Heap::erase(Entity entity) {
  auto itr = componentTypeMap.find(std::type_index(typeid(T)));
  if (itr != std::end(componentTypeMap)) {
    itr->second.erase(entity);
  }
}

template <typename... Types>
auto Heap::begin() -> Heap::iterator {
  return iterator(&componentTypeMap, {std::type_index(typeid(Types))...},
                  /*moveToEnd=*/false);
}

template <typename... Types>
auto Heap::end() -> Heap::iterator {
  return iterator(&componentTypeMap, {std::type_index(typeid(Types))...},
                  /*moveToEnd=*/true);
}
