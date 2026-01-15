#include "sprite.h"
#include <stdbool.h>

ECS_COMPONENT_DECLARE(Sprite);

void register_sprite_component(ecs_world_t *world) {
    ECS_COMPONENT_DEFINE(world, Sprite);
}
void sprite_init(Game *game, SDL_Texture *t, float rx, float ry, float size,
                 Sprite *sprite) {
    SDL_FRect src_rect = {
        .x = rx,
        .y = ry,
        .w = size,
        .h = size,
    };

    sprite->texture = t;
    sprite->src = src_rect;
}
