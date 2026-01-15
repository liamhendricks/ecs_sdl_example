#include "world.h"
#include "SDL3/SDL_log.h"
#include "core/tilemap.h"
#include "ecs/components/collision.h"
#include "ecs/components/gui.h"
#include "ecs/components/input.h"
#include "ecs/components/position.h"
#include "ecs/components/sprite.h"
#include "ecs/components/velocity.h"
#include "ecs/entities/gui/mouse.h"
#include "ecs/entities/player.h"
#include "ecs/systems/input.h"
#include "ecs/systems/move.h"
#include <stdlib.h>

ecs_world_t *create_world(Game *game) {
    ecs_world_t *world = ecs_init();

    register_all_components(world);
    register_all_systems(world, game);
    bool ok = register_entities(world, game);
    if (!ok) {
        SDL_Log("error creating entities");
        return NULL;
    }
    int map[7][3] = {{2, 3, 3}, {3, 3, 3}, {1, 1, 3}, {1, 0, 1},
                     {1, 1, 1}, {0, 2, 0}, {2, 2, 2}};
    create_tilemap(world, game, 7, 3, map, "assets/tilemap1.png");

    return world;
}

void register_all_components(ecs_world_t *world) {
    register_input_component(world);
    register_collision_component(world);
    register_ui_element_component(world);
    register_position_component(world);
    register_velocity_component(world);
    register_sprite_component(world);
}

void register_all_systems(ecs_world_t *world, Game *game) {
    register_input_system(world, game);
    register_move_system(world);
}

bool register_entities(ecs_world_t *world, Game *game) {
    g_mouse = create_mouse_entity(world, game);
    if (g_mouse == -1) {
        return false;
    }

    g_player = create_player_entity(world, game);
    if (g_player == -1) {
        return false;
    }

    return true;
}
