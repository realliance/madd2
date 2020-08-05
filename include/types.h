#pragma once
#include <stdint.h>
#include <map>
#include <unordered_map>

typedef uint64_t Entity;
typedef uint32_t ComponentType;
struct HeapEntry;
typedef std::map<Entity, HeapEntry> ComponentMap;
typedef std::unordered_map<ComponentType,ComponentMap> ComponentTypeMap;
