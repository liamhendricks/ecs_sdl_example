#pragma once

#include "ecs/components/sprite.h"
#include <SDL3/SDL.h>
#include <flecs.h>

void draw_sprites(ecs_world_t *world, SDL_Renderer *renderer);
void draw_sprite(Sprite sprite, float x, float y, SDL_Renderer *renderer);
bool is_sprite_visible(const Camera *cam, float screen_x, float screen_y,
                       float width, float height);
int compare_z_order(ecs_entity_t e1, const void *v1, ecs_entity_t e2,
                    const void *v2);
