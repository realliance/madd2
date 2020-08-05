#pragma once
#include "types.h"
#include <iostream>

struct HeapEntry{
  Entity entity;
  ComponentType componentType;
};

inline bool operator==(const HeapEntry& lhs, const HeapEntry& rhs){
    return lhs.entity == rhs.entity && lhs.componentType == rhs.componentType; 
}

std::ostream& operator<<(std::ostream& os, const HeapEntry& heapEntry);
