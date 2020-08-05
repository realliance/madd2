#include "heap_entry.h"

std::ostream& operator<<(std::ostream& os, const HeapEntry& heapEntry){
    os << "{ Entity: " << heapEntry.entity;
    os << " ComponentType: " << heapEntry.componentType << "}";
    return os;
}