#pragma once
#include "types.h"

class ECS{
  public:
    ECS();
    ~ECS();
    ECS& CreateEntity();
    ECS& DeleteEntity();
    ECS& AddComponent(Entity entity);
    ECS& RemoveComponent(Entity entity);
};