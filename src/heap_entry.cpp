#include "heap_entry.h"
#include <utility>

HeapEntry::HeapEntry():
  componentId(-1),
  data(nullptr),
  destruct([](){return;}) 
{}

HeapEntry::~HeapEntry(){
  destruct();
  destruct = [](){return;};
  componentId = -1;
  data = nullptr;
}

HeapEntry::HeapEntry(HeapEntry&& other) noexcept : 
  componentId(std::exchange(other.componentId, -1)),
  destruct(std::exchange(other.destruct, [](){return;}))
{}

HeapEntry& HeapEntry::operator=(HeapEntry&& other) noexcept{
  if(this != &other) { 
    destruct();
    destruct = std::exchange(other.destruct, [](){return;});
    componentId = std::exchange(other.componentId, -1);
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const HeapEntry& heapEntry){
  os << "{ ComponentId: " << heapEntry.componentId << " }";
  return os;
}