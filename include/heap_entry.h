#pragma once
#include <functional>
#include <iostream>

#include "types.h"

class HeapEntry {
 public:
  HeapEntry();
  ~HeapEntry();
  template <class T>
  HeapEntry(T* _data, ComponentId _componentId);

  // Move
  HeapEntry(HeapEntry&& other) noexcept;
  auto operator=(HeapEntry&& other) noexcept -> HeapEntry&;

  // Copy, deleted
  HeapEntry(const HeapEntry&) = delete;
  auto operator=(const HeapEntry&) -> HeapEntry& = delete;

  template <class T>
  auto to() -> const T&;
  // NOLINTNEXTLINE(cppcoreguidelines-non-private-member-variables-in-classes)
  ComponentId componentId{static_cast<ComponentId>(-1)};

 private:
  void* data{nullptr};
  std::function<void()> destruct;
};

template <class T>
HeapEntry::HeapEntry(T* _data, ComponentId _componentId)
  : componentId(_componentId),
    data(static_cast<void*>(_data)),
    destruct(
      [_data]() { delete _data; })
{}

template <class T>
auto HeapEntry::to() -> const T& {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  return *reinterpret_cast<T*>(data);
}

inline auto operator==(const HeapEntry& lhs, const HeapEntry& rhs) -> bool {
  return lhs.componentId == rhs.componentId;
}

auto operator<<(std::ostream& os, const HeapEntry& heapEntry) -> std::ostream&;
