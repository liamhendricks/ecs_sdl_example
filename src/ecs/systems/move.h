#pragma once

#include <flecs.h>

void MoveSystem(ecs_iter_t *it);
void register_move_system(ecs_world_t *world);
