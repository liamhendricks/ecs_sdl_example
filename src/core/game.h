#pragma once

#include "camera.h"
#include "vector_2.h"
#include <SDL3/SDL.h>
#include <flecs.h>

typedef struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    ecs_world_t *world;
    Vector2 window_size;
    Camera *camera;

    char *title;
    bool running;
    Uint64 delta_time;
    Uint64 last_frame_time;
    Uint32 target_frame_time;
    Uint64 fps;
    bool vsync;

    ecs_entity_t mouse_entity;
} Game;

void init_camera(Game *game, int w, int h);
bool init_application(Game *game);
void main_loop(Game *game);
void tick(Game *game);
void update(Game *game);
void render(Game *game);
void exit_application(Game *game);
int calculate_optimal_logical_size(int window_w, int window_h);
