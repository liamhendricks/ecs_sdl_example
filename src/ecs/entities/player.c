#include "player.h"
#include "core/game.h"
#include "core/tilemap.h"
#include "ecs/components/collision.h"
#include "ecs/components/position.h"
#include "ecs/components/sprite.h"
#include <SDL3/SDL.h>
#include <flecs.h>

ecs_entity_t create_player_entity(ecs_world_t *world, Game *game) {
    SDL_Texture *t = load_tilemap_texture(game, "./assets/gui.png");
    Sprite player_sprite;
    sprite_init(game, t, 32, 0, t->w, &player_sprite);

    ecs_entity_t player = ecs_new(world);
    ecs_set(world, player, Position, {-32.0f, 16.0f});
    ecs_set(world, player, Sprite, {player_sprite.texture, player_sprite.src});
    ecs_set(world, player, Collision,
            {.enabled = true,
             .height = SPRITE_SIZE,
             .width = SPRITE_SIZE,
             .pickable = true,
             .layers = COLLISION_LAYER_PLAYER,
             .mask = COLLISION_LAYER_TERRAIN | COLLISION_LAYER_MOUSE});
    ecs_set_name(world, player, "Player");

    return player;
}
