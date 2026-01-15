#pragma once

#include "ecs/components/collision.h"
#include "game.h"
#include <flecs.h>

typedef struct {
    int src_x, src_y;
    Collision collision;
} TileDefinition;

typedef struct {
} Map;

typedef enum {
    HALF_SPRITE_SIZE = 16,
    SPRITE_SIZE = 32,
    TILESET_SIZE = 512,
} Constants;

bool create_tilemap(ecs_world_t *world, Game *game, int rows, int cols,
                    int tile_data[rows][cols], const char *filepath);
SDL_Texture *load_tilemap_texture(Game *game, const char *filepath);
