#include "draw_sprite.h"
#include "SDL3/SDL_rect.h"
#include "core/camera.h"
#include "ecs/components/gui.h"
#include "ecs/components/position.h"
#include "ecs/components/sprite.h"
#include "flecs.h"
#include <SDL3/SDL.h>

void draw_sprites(ecs_world_t *world, SDL_Renderer *renderer) {
    ecs_query_t *query =
        ecs_query(world, {.terms = {{ecs_id(Position)},
                                    {ecs_id(Sprite)},
                                    {ecs_id(UIElement), .oper = EcsNot}}});
    //.order_by = ecs_id(Position),
    //.order_by_callback = compare_z_order});
    Game *game = ecs_get_ctx(world);

    ecs_iter_t it = ecs_query_iter(world, query);
    while (ecs_query_next(&it)) {
        Position *positions = ecs_field(&it, Position, 0);
        Sprite *sprites = ecs_field(&it, Sprite, 1);

        for (int i = 0; i < it.count; i++) {
            float screen_x, screen_y;
            world_to_screen(game->camera, positions[i].x, positions[i].y,
                            &screen_x, &screen_y);

            // frustum culling
            if (sprites[i].texture &&
                is_sprite_visible(game->camera, screen_x, screen_y,
                                  sprites[i].src.w, sprites[i].src.h)) {
                draw_sprite(sprites[i], screen_x, screen_y, renderer);
            }
        }
    }

    ecs_query_fini(query);
}

void draw_sprite(Sprite sprite, float x, float y, SDL_Renderer *renderer) {
    SDL_FRect dst_rect = {.x = x, .y = y, .w = sprite.src.w, .h = sprite.src.h};
    SDL_RenderTexture(renderer, sprite.texture, &sprite.src, &dst_rect);
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_FRect or = dst_rect;
    // SDL_RenderRect(renderer, &or);
}

bool is_sprite_visible(const Camera *cam, float screen_x, float screen_y,
                       float width, float height) {
    return (screen_x + width > 0 && screen_x < cam->viewport.w &&
            screen_y + height > 0 && screen_y < cam->viewport.h);
}

int compare_z_order(ecs_entity_t e1, const void *v1, ecs_entity_t e2,
                    const void *v2) {
    const Position *d1 = v1;
    const Position *d2 = v2;
    return (d1->z_order < d2->z_order) - (d1->z_order > d2->z_order);
}
