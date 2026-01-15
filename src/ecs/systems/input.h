#pragma once

#include "core/game.h"
#include "ecs/components/position.h"
#include <SDL3/SDL.h>
#include <flecs.h>

void InputSystem(ecs_iter_t *it);
void register_input_system(ecs_world_t *world, Game *game);
void move_camera(Camera *camera, float dx, float dy);
void move_position(Position *position, float dx, float dy);
