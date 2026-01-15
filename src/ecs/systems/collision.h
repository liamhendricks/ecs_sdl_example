#pragma once

#include "core/game.h"
#include "ecs/components/collision.h"
#include "ecs/components/position.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

static bool check_aabb_collision(float x1, float y1, float w1, float h1,
                                 float x2, float y2, float w2, float h2);
static void get_isometric_bounds(Position *pos, Collision *col,
                                 SDL_FRect *bounds);
void handle_collisions(ecs_world_t *world, Game *game);
