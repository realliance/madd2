#include "component_heap_iterator_base.h"

#include <algorithm>
#include <ext/alloc_traits.h>
#include <iterator>
#include <map>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

iteratorBase::iteratorBase(ComponentTypeMap* componentTypeMap,
                           const std::vector<std::type_index>& componentTypes,
                           bool moveToEnd)
  : componentTypes(componentTypes), atEnd(moveToEnd) {
  if (atEnd) {
    return;
  }
  if (componentTypeMap->empty()) {
    atEnd = true;
    return;
  }

  Entity e = 0;
  bool first = true;
  bool match = true;
  for (const auto& type : componentTypes) {
    auto componentTypeMapItr = componentTypeMap->find(type);
    if (componentTypeMapItr == componentTypeMap->end()) {
      atEnd = true;
      return;
    }
    componentIterators.emplace_back(componentTypeMapItr->second.begin());
    componentMaps.push_back(&(componentTypeMapItr->second));
    if (componentIterators.front() == std::end(*componentMaps.front())) {
      atEnd = true;
      return;
    }
    if (match && e != (componentIterators.front())->first) {
      if (first) {
        e = (componentIterators.front())->first;
      } else {
        match = false;
      }
    }
  }
  if (match) {
    return;
  }
  next();
}

auto iteratorBase::next() -> iteratorBase& {
  auto componentMapsItr = componentMaps.begin();
  for (auto& componentIterator : componentIterators) {
    componentIterator++;
    if ((**componentMapsItr++).end() == componentIterator) {
      atEnd = true;
      return *this;
    }
  }
  Entity e = (**std::max_element(std::begin(componentIterators), std::end(componentIterators), compareComponentIterators)).first;
  auto predicate = [e](const ComponentMap::const_iterator& ci) { return ci->first == e; };

  while (!(std::all_of(std::begin(componentIterators), std::end(componentIterators), predicate))) {
    auto minEntityIteratorItr = std::min_element(std::begin(componentIterators), std::end(componentIterators), compareComponentIterators);
    (*minEntityIteratorItr)++;
    auto minEntityIteratorEnd = std::end(*componentMaps.at(std::distance(std::begin(componentIterators), minEntityIteratorItr)));
    if (*minEntityIteratorItr == minEntityIteratorEnd) {
      atEnd = true;
      return *this;
    }
  }
  return *this;
}

auto iteratorBase::compareComponentIterators(
  const ComponentMap::const_iterator& lhs,
  const ComponentMap::const_iterator& rhs) -> bool {
  return lhs->first < rhs->first;
}

auto iteratorBase::operator==(const iteratorBase& other) const -> bool {
  if (atEnd != other.atEnd) {
    return false;
  }
  if (componentTypes.size() != other.componentTypes.size()) {
    return false;
  }
  if (!std::equal(componentTypes.begin(), componentTypes.end(),
                  other.componentTypes.begin())) {
    return false;
  }
  if (atEnd) {
    return true;
  }
  return other.componentIterators.front() == componentIterators.front();
}

auto iteratorBase::operator!=(const iteratorBase& other) const -> bool {
  return !operator==(other);
}
