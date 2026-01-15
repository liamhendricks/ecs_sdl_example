#include "velocity.h"

ECS_COMPONENT_DECLARE(Velocity);

void register_velocity_component(ecs_world_t *world) {
    ECS_COMPONENT_DEFINE(world, Velocity);
}
