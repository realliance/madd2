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
  HeapEntry& operator=(HeapEntry&& other) noexcept;
  
  //Copy, deleted
  HeapEntry(const HeapEntry&) = delete;
  HeapEntry& operator=(const HeapEntry&) = delete;

  template<class T> const T& to();
  ComponentId componentId;
private:
  void* data;
  std::function<void()>  destruct;
};

template<class T>
HeapEntry::HeapEntry(T* _data,ComponentId _componentId):
  componentId(_componentId),
  data(static_cast<void*>(_data)),
  destruct([_data](){delete _data;})
  {}

template<class T>
const T& HeapEntry::to(){
  return *reinterpret_cast<T*>(data);
}

inline bool operator==(const HeapEntry& lhs, const HeapEntry& rhs){
    return lhs.componentId == rhs.componentId; 
}

std::ostream& operator<<(std::ostream& os, const HeapEntry& component);
