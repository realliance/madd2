#pragma once
#include <any>
#include <iostream>
#include <iterator>
#include <map>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include "component_heap_iterator_base.h"
#include "entity.h"
using ComponentMap = std::map<Entity, std::any>;
using ComponentTypeMap = std::unordered_map<std::type_index, ComponentMap>;
template <typename T>
concept PlainOldData = std::is_standard_layout_v<T>&& std::is_trivial_v<T>;
template <typename T>
concept NotPointer = std::negation_v<std::is_pointer<T>>;

enum ReservedEntity {
  LAST_ENTITY = static_cast<Entity>(-1),
  ERROR_ENTITY = 0,
  FIRST_VALID_ENTITY  // Must be last ReservedEntity Id.
};

class ComponentHeap {
  ComponentTypeMap componentTypeMap;

 public:
  template <typename... Types>
  class const_iterator : public iteratorBase {
    friend ComponentHeap;
    explicit const_iterator(const ComponentTypeMap* componentTypeMap,
                            bool moveToEnd = false)
      : iteratorBase(componentTypeMap, {std::type_index(typeid(Types))...}, moveToEnd) {}

    static auto compareComponentIterators(ComponentMap::const_iterator& lhs,
                                          ComponentMap::const_iterator& rhs) -> bool;

   public:
    auto operator++() -> const_iterator<Types...>&;
    auto operator++(int) -> const_iterator<Types...>;
    auto operator*() const -> std::tuple<const Types&...>;
    // iterator traits
    using difference_type = std::ptrdiff_t;
    using pointer = const std::tuple<const Types*...>;
    using reference = const std::tuple<const Types&...>;
    using iterator_category = std::input_iterator_tag;
  };

  template <typename... Types>
  class TypeSet {
    const ComponentTypeMap* componentTypeMap;

   public:
    explicit TypeSet(const ComponentTypeMap* componentTypeMap)
      : componentTypeMap(componentTypeMap) {}

    auto begin() const -> const_iterator<Types...>;
    auto end() const -> const_iterator<Types...>;
  };

  template <typename... Types>
  auto toTypeSet() const -> TypeSet<Types...>;
  template <typename T>
  void insert(Entity entity, T&& component) requires PlainOldData<T>&& NotPointer<T>;
  template <typename T>
  void erase(Entity entity);
  void clear();
  auto data() -> ComponentTypeMap*;
};

template <typename... Types>
auto ComponentHeap::toTypeSet() const -> TypeSet<Types...> {
  return TypeSet<Types...>(&componentTypeMap);
}

template <typename T>
void ComponentHeap::insert(
  Entity entity, T&& component) requires PlainOldData<T>&& NotPointer<T> {
  componentTypeMap[std::type_index(typeid(T))].insert_or_assign(entity, component);
}

template <typename T>
void ComponentHeap::erase(Entity entity) {
  auto itr = componentTypeMap.find(std::type_index(typeid(T)));
  if (itr != std::end(componentTypeMap)) {
    auto iitr = itr->second.find(entity);
    if (iitr != itr->second.end()) {
      itr->second.erase(entity);
    }
  }
}

template <typename... Types>
auto ComponentHeap::const_iterator<Types...>::operator++() -> const_iterator<Types...>& {
  next();
  return *this;
}

template <typename... Types>
auto ComponentHeap::const_iterator<Types...>::operator++(int) -> const_iterator<Types...> {
  const_iterator tmp(*this);
  next();
  return tmp;
}

template <typename T, typename... Types>
auto dereference(std::vector<ComponentMap::const_iterator>::const_iterator itr, auto tuple) {
  if constexpr (sizeof...(Types) == 0) {
    return std::tuple_cat(tuple, std::forward_as_tuple(std::any_cast<const T&>((**itr).second)));
  } else {
    return dereference<Types...>(itr + 1, std::tuple_cat(tuple, std::forward_as_tuple(std::any_cast<const T&>((**itr).second))));
  }
}

template <typename... Types>
auto ComponentHeap::const_iterator<Types...>::operator*() const -> std::tuple<const Types&...> {
  return dereference<Types...>(componentIterators.begin(), std::tuple<>{});
}

template <typename... Types>
auto ComponentHeap::TypeSet<Types...>::begin() const -> ComponentHeap::const_iterator<Types...> {
  return const_iterator<Types...>(componentTypeMap, /*moveToEnd=*/false);
}

template <typename... Types>
auto ComponentHeap::TypeSet<Types...>::end() const -> ComponentHeap::const_iterator<Types...> {
  return const_iterator<Types...>(componentTypeMap, /*moveToEnd=*/true);
}
