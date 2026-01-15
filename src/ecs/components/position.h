#pragma once

#include <flecs.h>

typedef struct {
    double x, y;
    float z_order;
} Position;

extern ECS_COMPONENT_DECLARE(Position);
void register_position_component(ecs_world_t *world);
