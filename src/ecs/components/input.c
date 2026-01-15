#include "input.h"

ECS_COMPONENT_DECLARE(InputState);

void register_input_component(ecs_world_t *world) {
    ECS_COMPONENT_DEFINE(world, InputState);

    ecs_singleton_set(world, InputState, {0});
}
