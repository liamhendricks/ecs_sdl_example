#pragma once

#include <flecs.h>
#include <stdbool.h>

typedef enum CollisionLayer {
    COLLISION_LAYER_TERRAIN = 1 << 0,
    COLLISION_LAYER_PLAYER = 1 << 1,
    COLLISION_LAYER_ENEMY = 1 << 2,
    COLLISION_LAYER_PROJECTILE = 1 << 3,
    COLLISION_LAYER_ITEM = 1 << 4,
    COLLISION_LAYER_MOUSE = 1 << 5
} CollisionLayer;

typedef struct {
    float width;
    float height;
    CollisionLayer layers;
    CollisionLayer mask;
    bool enabled;
    bool pickable;
} Collision;

extern ECS_COMPONENT_DECLARE(Collision);
void register_collision_component(ecs_world_t *world);
