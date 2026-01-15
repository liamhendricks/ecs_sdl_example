#pragma once

#include <flecs.h>

typedef struct {
    double x, y;
} Velocity;

extern ECS_COMPONENT_DECLARE(Velocity);
void register_velocity_component(ecs_world_t *world);
