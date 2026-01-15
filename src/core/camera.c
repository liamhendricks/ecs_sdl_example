#include "camera.h"

void world_to_screen(const Camera *cam, float world_x, float world_y,
                     float *screen_x, float *screen_y) {
    *screen_x = (world_x - cam->x) * cam->zoom + (cam->viewport.w / 2.0f);
    *screen_y = (world_y - cam->y) * cam->zoom + (cam->viewport.h / 2.0f);
}

void screen_to_world(const Camera *cam, float screen_x, float screen_y,
                     float *world_x, float *world_y) {
    *world_x = (screen_x - (cam->viewport.w / 2.0f)) / cam->zoom + cam->x;
    *world_y = (screen_y - (cam->viewport.h / 2.0f)) / cam->zoom + cam->y;
}
