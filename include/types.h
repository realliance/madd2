#pragma once
#include <cstdint>
#include <map>
#include <unordered_map>

typedef uint64_t Entity;
using ComponentType = uint32_t;
using ComponentId = uint64_t;
class HeapEntry;
using ComponentMap = std::map<Entity, HeapEntry>;
using ComponentTypeMap = std::unordered_map<ComponentType, ComponentMap>;
