#pragma once

#include <flecs.h>
#include <stdbool.h>
#include "vector_2.h"

typedef struct InputState {
    Vector2 mouse_pos;
    bool quit;
    bool up;
    bool down;
    bool left;
    bool right;
    bool fire;
    bool mouse_l;
    bool mouse_r;
} InputState;

extern ECS_COMPONENT_DECLARE(InputState);
void register_input_component(ecs_world_t *world);
