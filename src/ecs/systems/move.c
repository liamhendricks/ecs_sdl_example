#include "move.h"
#include "ecs/components/position.h"
#include "ecs/components/velocity.h"
#include "flecs.h"

void MoveSystem(ecs_iter_t *it) {
    Position *p = ecs_field(it, Position, 0);
    Velocity *v = ecs_field(it, Velocity, 1);

    for (int i = 0; i < it->count; i++) {
        p[i].x += v[i].x * it->delta_time;
        p[i].y += v[i].y * it->delta_time;
    }
}

void register_move_system(ecs_world_t *world) {
    ECS_SYSTEM(world, MoveSystem, EcsOnUpdate, Position, Velocity);
}
