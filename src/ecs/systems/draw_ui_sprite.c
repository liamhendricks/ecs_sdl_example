#include "draw_ui_sprite.h"
#include "draw_sprite.h"
#include "ecs/components/gui.h"
#include "ecs/components/position.h"
#include "ecs/components/sprite.h"
#include "flecs.h"
#include <SDL3/SDL.h>

void draw_ui_sprites(ecs_world_t *world, SDL_Renderer *renderer) {
    ecs_query_t *query =
        ecs_query(world, {.terms = {{ecs_id(Position)},
                                    {ecs_id(Sprite)},
                                    {ecs_id(UIElement), .oper = EcsIsA}}});
    Game *game = ecs_get_ctx(world);

    ecs_iter_t it = ecs_query_iter(world, query);
    while (ecs_query_next(&it)) {
        Position *positions = ecs_field(&it, Position, 0);
        Sprite *sprites = ecs_field(&it, Sprite, 1);

        for (int i = 0; i < it.count; i++) {
            if (sprites[i].texture) {
                float screen_x, screen_y, world_x, world_y;
                draw_sprite(sprites[i], positions[i].x, positions[i].y,
                            renderer);
            }
        }
    }

    ecs_query_fini(query);
}
