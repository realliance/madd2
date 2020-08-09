#include "heap_entry.h"

#include <utility>

HeapEntry::HeapEntry()
  :

    destruct([]() {}) {}

HeapEntry::~HeapEntry() {
  destruct();
  destruct = []() {};
  componentId = -1;
  data = nullptr;
}

HeapEntry::HeapEntry(HeapEntry&& other) noexcept
  : componentId(std::exchange(other.componentId, -1)),
    destruct(std::exchange(other.destruct, []() {})) {}

auto HeapEntry::operator=(HeapEntry&& other) noexcept -> HeapEntry& {
  if (this != &other) {
    destruct();
    destruct = std::exchange(other.destruct, []() {});
    componentId = std::exchange(other.componentId, -1);
  }
  return *this;
}

auto operator<<(std::ostream& os, const HeapEntry& heapEntry) -> std::ostream& {
  os << "{ ComponentId: " << heapEntry.componentId << " }";
  return os;
}