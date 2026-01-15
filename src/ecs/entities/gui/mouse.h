#pragma once

#include "core/game.h"
#include <flecs.h>

ecs_entity_t create_mouse_entity(ecs_world_t *world, Game *game);
