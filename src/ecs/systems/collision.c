#include "collision.h"
#include "SDL3/SDL_log.h"
#include "core/game.h"
#include "ecs/components/collision.h"
#include "ecs/components/position.h"
#include <flecs.h>

// check collision between two AABBs in screen space
static bool check_aabb_collision(float x1, float y1, float w1, float h1,
                                 float x2, float y2, float w2, float h2) {
    return (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
}

// get the screen-space bounding box for an isometric entity
static void get_isometric_bounds(Position *pos, Collision *col,
                                 SDL_FRect *bounds) {
    bounds->x = pos->x;
    bounds->y = pos->y;
    bounds->w = col->width;
    bounds->h = col->height;
}

void handle_collisions(ecs_world_t *world, Game *game) {
    ecs_query_t *query =
        ecs_query(world, {.terms = {{ecs_id(Position)}, {ecs_id(Collision)}}});
    ecs_iter_t it = ecs_query_iter(world, query);

    Position positions[256];
    Collision collisions[256];
    int count = 0;

    while (ecs_query_next(&it)) {
        Position *next_positions = ecs_field(&it, Position, 0);
        Collision *next_collisions = ecs_field(&it, Collision, 1);
        for (int i = 0; i < it.count; i++) {
            positions[i] = next_positions[i];
            collisions[i] = next_collisions[i];
            count++;
        }
    }

    // simple broad-phase: check each entity against others
    for (int i = 0; i < count; i++) {
        if (!collisions[i].enabled)
            continue;

        Position *pos1 = &positions[i];
        Collision *col1 = &collisions[i];
        SDL_FRect bounds1;
        get_isometric_bounds(pos1, col1, &bounds1);

        for (int j = i + 1; j < count; j++) {
            if (!collisions[j].enabled)
                continue;

            Position *pos2 = &positions[j];
            Collision *col2 = &collisions[j];

            // check layer masks
            if (!(col1->layers & col2->mask) && !(col2->layers & col1->mask)) {
                continue;
            }

            SDL_FRect bounds2;
            get_isometric_bounds(pos2, col2, &bounds2);

            //   check bounding box collision in screen space
            if (check_aabb_collision(bounds1.x, bounds1.y, bounds1.w, bounds1.h,
                                     bounds2.x, bounds2.y, bounds2.w,
                                     bounds2.h)) {

                // handle collision
                if (col1->pickable || col2->pickable) {
                    // pickable
                    SDL_Log("pickable");
                    SDL_Log("col1: x %f y %f", bounds1.x, bounds1.y);
                    SDL_Log("col2: x %f y %f", bounds2.x, bounds2.y);
                } else {
                    // solid collision
                    SDL_Log("solid");
                }
            }
        }
    }
}
