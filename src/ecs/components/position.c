#include "position.h"

ECS_COMPONENT_DECLARE(Position);

void register_position_component(ecs_world_t *world) {
    ECS_COMPONENT_DEFINE(world, Position);
}
