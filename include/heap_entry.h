#pragma once
#include <functional>
#include <iostream>
#include "types.h"


class HeapEntry {
public:
  HeapEntry();
  ~HeapEntry();
  template<class T> HeapEntry(T* _data,ComponentId _componentId);

  //Move
  HeapEntry(HeapEntry&& other) noexcept;
  auto operator=(HeapEntry&& other) noexcept -> HeapEntry&;

  //Copy, deleted
  HeapEntry(const HeapEntry&) = delete;
  auto operator=(const HeapEntry&) -> HeapEntry& = delete;

  template <class T>
  auto to() -> const T&;
  ComponentId componentId{static_cast<ComponentId>(-1)}; //NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)

 private:
  void* data{nullptr};
  std::function<void()>  destruct;
};

template<class T>
HeapEntry::HeapEntry(T* _data,ComponentId _componentId):
  componentId(_componentId),
  data(static_cast<void*>(_data)),
  destruct([_data](){delete _data;}) //NOLINT(cppcoreguidelines-owning-memory)
  {}

template <class T>
auto HeapEntry::to() -> const T& {
  return *reinterpret_cast<T*>(data); //NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
}

inline auto operator==(const HeapEntry& lhs, const HeapEntry& rhs) -> bool {
  return lhs.componentId == rhs.componentId;
}

auto operator<<(std::ostream& os, const HeapEntry& heapEntry) -> std::ostream&;
