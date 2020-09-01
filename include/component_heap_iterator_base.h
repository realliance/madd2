#pragma once
#include <any>
#include <cstdint>
#include <map>
#include <typeindex>
#include <unordered_map>
#include <vector>

using Entity = uint64_t;
using ComponentMap = std::map<Entity, std::any>;
using ComponentTypeMap = std::unordered_map<std::type_index, ComponentMap>;
class ComponentHeap;

class iteratorBase {
 public:
  friend ComponentHeap;
  std::vector<ComponentMap::const_iterator> componentIterators;
  std::vector<ComponentMap const*> componentMaps;
  std::vector<std::type_index> componentTypes;
  bool atEnd;
  iteratorBase(ComponentTypeMap* componentTypeMap,
               const std::vector<std::type_index>& componentTypes,
               bool moveToEnd = false);
  static auto compareComponentIterators(const ComponentMap::const_iterator& lhs,
                                        const ComponentMap::const_iterator& rhs) -> bool;

 public:
  auto next() -> iteratorBase&;
  auto operator==(const iteratorBase& other) const -> bool;
  auto operator!=(const iteratorBase& other) const -> bool;
};
