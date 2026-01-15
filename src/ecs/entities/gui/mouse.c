#include "mouse.h"
#include "core/tilemap.h"
#include "ecs/components/collision.h"
#include "ecs/components/gui.h"
#include "ecs/components/position.h"
#include "ecs/components/sprite.h"
#include "flecs.h"

ecs_entity_t create_mouse_entity(ecs_world_t *world, Game *game) {
    SDL_Texture *t = load_tilemap_texture(game, "./assets/gui.png");
    Sprite mouse_sprite;
    sprite_init(game, t, 0, 0, SPRITE_SIZE, &mouse_sprite);

    ecs_entity_t mouse = ecs_new(world);
    ecs_set(world, mouse, Position, {0.0f, 0.0f});
    ecs_set(world, mouse, Sprite, {mouse_sprite.texture, mouse_sprite.src});
    ecs_set(world, mouse, Collision,
            {.enabled = true,
             .height = SPRITE_SIZE,
             .width = SPRITE_SIZE,
             .pickable = true,
             .layers = COLLISION_LAYER_MOUSE,
             .mask = COLLISION_LAYER_PLAYER});
    ecs_set(world, mouse, UIElement, {true});
    ecs_set_name(world, mouse, "MouseCursor");

    return mouse;
}
