#pragma once
#include <any>
#include <cstdint>
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
using Entity = uint64_t;
using ComponentMap = std::map<Entity, std::any>;
using ComponentTypeMap = std::unordered_map<std::type_index, ComponentMap>;
template <typename T>
concept PlainOldData = std::is_pod_v<T>;
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
  class iterator : public iteratorBase {
    friend ComponentHeap;
    explicit iterator(ComponentTypeMap* componentTypeMap,
                      bool moveToEnd = false)
      : iteratorBase(componentTypeMap, {std::type_index(typeid(Types))...},
                     moveToEnd) {}
    static auto compareComponentIterators(const ComponentMap::iterator& lhs,
                                          const ComponentMap::iterator& rhs)
      -> bool;

   public:
    auto operator++() -> iterator<Types...>&;
    auto operator++(int) -> iterator<Types...>;
    constexpr auto operator*() const -> std::tuple<const Types&&...>;
    // iterator traits
    using difference_type = std::ptrdiff_t;
    using pointer = const std::tuple<Types*...>;
    using reference = const std::vector<Types&...>;
    using iterator_category = std::input_iterator_tag;
  };

  template <typename... Types>
  class TypeSet {
    ComponentTypeMap* componentTypeMap;

   public:
    explicit TypeSet(ComponentTypeMap* componentTypeMap)
      : componentTypeMap(componentTypeMap) {}

    auto begin() -> iterator<Types...>;
    auto end() -> iterator<Types...>;
  };

  template <typename... Types>
  auto toTypeSet() -> TypeSet<Types...>;
  template <typename T>
  void insert(Entity entity,
              T&& component) requires PlainOldData<T>&& NotPointer<T>;
  template <typename T>
  void erase(Entity entity);
  void clear();
  auto data() -> ComponentTypeMap*;
};

template <typename... Types>
auto ComponentHeap::toTypeSet() -> TypeSet<Types...> {
  return TypeSet<Types...>(&componentTypeMap);
}

template <typename T>
void ComponentHeap::insert(
  Entity entity, T&& component) requires PlainOldData<T>&& NotPointer<T> {
  componentTypeMap[std::type_index(typeid(T))].insert_or_assign(entity,
                                                                component);
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
auto ComponentHeap::iterator<Types...>::operator++() -> iterator<Types...>& {
  next();
  return *this;
}

template <typename... Types>
auto ComponentHeap::iterator<Types...>::operator++(int) -> iterator<Types...> {
  iterator tmp(*this);
  next();
  return tmp;
}

template <typename T, typename... Types>
constexpr auto dereference(
  std::vector<ComponentMap::iterator>::const_iterator itr)
  -> std::tuple<const T&&, const Types&&...> {
  if constexpr (sizeof...(Types) == 0) {
    return std::forward_as_tuple<const T&&>(
      std::any_cast<const T&&>(std::move((*itr)->second)));
  } else {
    return std::tuple_cat(
      std::forward_as_tuple<const T&&>(
        std::any_cast<const T&&>(std::move((*itr)->second))),
      dereference<Types...>(++itr));
  }
}

template <typename... Types>
constexpr auto ComponentHeap::iterator<Types...>::operator*() const
  -> std::tuple<const Types&&...> {
  return dereference<Types...>(componentIterators.begin());
}

template <typename... Types>
auto ComponentHeap::TypeSet<Types...>::begin()
  -> ComponentHeap::iterator<Types...> {
  return iterator<Types...>(componentTypeMap,
                            /*moveToEnd=*/false);
}

template <typename... Types>
auto ComponentHeap::TypeSet<Types...>::end()
  -> ComponentHeap::iterator<Types...> {
  return iterator<Types...>(componentTypeMap,
                            /*moveToEnd=*/true);
}
