#pragma once

#include "game.h"
#include <flecs.h>

static ecs_entity_t g_mouse = 0;
static ecs_entity_t g_player = 0;

ecs_world_t *create_world(Game *game);
void register_all_components(ecs_world_t *world);
void register_all_systems(ecs_world_t *world, Game *game);
bool register_entities(ecs_world_t *world, Game *game);
