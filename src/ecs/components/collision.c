#include "collision.h"

ECS_COMPONENT_DECLARE(Collision);

void register_collision_component(ecs_world_t *world) {
    ECS_COMPONENT_DEFINE(world, Collision);
}
