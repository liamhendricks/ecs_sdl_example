#pragma once

#include "core/game.h"
#include <flecs.h>

ecs_entity_t create_player_entity(ecs_world_t *world, Game *game);
