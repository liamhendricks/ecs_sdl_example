#include "tilemap.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "ecs/components/collision.h"
#include "ecs/components/position.h"
#include "ecs/components/sprite.h"
#include <flecs.h>
#include <math.h>

Uint8 COLOR_MASK_R = 0xFF;
Uint8 COLOR_MASK_G = 0x00;
Uint8 COLOR_MASK_B = 0xFF;

const Collision environment_collider_1t = {HALF_SPRITE_SIZE,
                                           HALF_SPRITE_SIZE,
                                           COLLISION_LAYER_TERRAIN,
                                           COLLISION_LAYER_TERRAIN,
                                           true,
                                           false};
const Collision non_collider = {0, 0, 0, 0, false, false};

TileDefinition tile_defs[] = {
    [0] = {0, 0, non_collider},             // none
    [1] = {0, 0, environment_collider_1t},  // first sprite
    [2] = {32, 0, environment_collider_1t}, // second sprite
    [3] = {64, 0, non_collider},            // etc
    [4] = {96, 0, non_collider}};

bool create_tilemap(ecs_world_t *world, Game *game, int rows, int cols,
                    int tile_data[rows][cols], const char *filepath) {

    SDL_Texture *texture = load_tilemap_texture(game, filepath);
    if (texture == NULL) {
        SDL_Log("unable to create texture");
        return false;
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int tile_id = tile_data[row][col];
            if (tile_id == 0)
                continue;

            // create tile entities
            ecs_entity_t tile_entity = ecs_new(world);

            // isometric projection
            float iso_x = (col - row) * (SPRITE_SIZE / 2.0f);
            float iso_y = (col + row) * (SPRITE_SIZE / 4.0f);
            float z_order = iso_y;
            SDL_Log("x: %f y: %f", iso_x, iso_y);

            iso_x = roundf(iso_x);
            iso_y = roundf(iso_y);

            // set position
            ecs_set(world, tile_entity, Position,
                    {.x = -iso_x, .y = iso_y, .z_order = z_order});

            TileDefinition tileset_def = tile_defs[tile_id];

            Sprite sprite_entity;
            sprite_init(game, texture, tileset_def.src_x, tileset_def.src_y,
                        SPRITE_SIZE, &sprite_entity);

            // set sprite
            ecs_set(world, tile_entity, Sprite,
                    {sprite_entity.texture, sprite_entity.src});

            if (tileset_def.collision.enabled) {
                SDL_Log("coll");
                ecs_set(world, tile_entity, Collision,
                        {.enabled = tileset_def.collision.enabled,
                         .pickable = tileset_def.collision.pickable,
                         .layers = tileset_def.collision.layers,
                         .mask = tileset_def.collision.mask,
                         .height = tileset_def.collision.height,
                         .width = tileset_def.collision.width});
            }
        }
    }
    return true;
}

SDL_Texture *load_tilemap_texture(Game *game, const char *filepath) {
    SDL_Surface *surface = SDL_LoadPNG(filepath);
    if (surface == NULL) {
        SDL_Log("unable to load tilemap");
        return NULL;
    }

    // color key alpha masking
    const SDL_PixelFormatDetails *details =
        SDL_GetPixelFormatDetails(surface->format);
    SDL_Palette *palette = SDL_GetSurfacePalette(surface);
    Uint32 color_key =
        SDL_MapRGB(details, palette, COLOR_MASK_R, COLOR_MASK_G, COLOR_MASK_B);
    SDL_SetSurfaceColorKey(surface, true, color_key);
    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(game->renderer, surface);

    if (texture) {
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_PIXELART);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }

    SDL_DestroySurface(surface);
    return texture;
}
