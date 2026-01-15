#pragma once

#include "core/game.h"
#include <SDL3/SDL.h>
#include <flecs.h>

typedef struct {
    SDL_Texture *texture;
    SDL_FRect src;
} Sprite;

extern ECS_COMPONENT_DECLARE(Sprite);
void register_sprite_component(ecs_world_t *world);
void sprite_init(Game *game, SDL_Texture *t, float rx, float ry, float size,
                 Sprite *sprite);
