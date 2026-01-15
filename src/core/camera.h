#pragma once

#include <SDL3/SDL.h>

typedef struct {
    float x, y;
    float zoom;
    SDL_FRect viewport;
} Camera;

void world_to_screen(const Camera *cam, float world_x, float world_y,
                     float *screen_x, float *screen_y);
void screen_to_world(const Camera *cam, float screen_x, float screen_y,
                     float *world_x, float *world_y);
