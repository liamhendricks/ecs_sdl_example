#include "game.h"
#include "camera.h"
#include "ecs/components/input.h"
#include "ecs/components/sprite.h"
#include "ecs/systems/collision.h"
#include "ecs/systems/draw_sprite.h"
#include "ecs/systems/draw_ui_sprite.h"
#include "world.h"
#include <SDL3/SDL.h>
#include <stdio.h>

bool init_application(Game *game) {
    SDL_Init(SDL_INIT_VIDEO);
    game->window_size.x = 640.0;
    game->window_size.y = 360.0;
    game->title = "ECS SDL EXAMPLE";
    SDL_PropertiesID props = SDL_CreateProperties();
    if (props == 0) {
        SDL_Log("Unable to create properties: %s", SDL_GetError());
        return false;
    }

    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING,
                          game->title);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER,
                          game->window_size.x);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER,
                          game->window_size.y);

    SDL_Window *window = SDL_CreateWindowWithProperties(props);
    if (window == NULL) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return false;
    }
    SDL_SetWindowFullscreen(window, true);
    game->window = window;
    if (game->window == NULL) {
        SDL_Log("error initializing SDL window");
        return false;
    }

    game->renderer = SDL_CreateRenderer(game->window, "opengl");
    if (game->renderer == NULL) {
        SDL_Log("error initializing SDL renderer");
        return false;
    }

    SDL_Log("available hardware renderers:");
    for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
        SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
    }

    bool ok = SDL_SetRenderLogicalPresentation(
        game->renderer, game->window_size.x, game->window_size.y,
        SDL_LOGICAL_PRESENTATION_STRETCH);
    if (!ok) {
        SDL_Log("error setting logical window presentation for renderer: %s",
                SDL_GetRendererName(game->renderer));
        return ok;
    }

    SDL_HideCursor();

    SDL_Log("using renderer: %s", SDL_GetRendererName(game->renderer));

    game->camera = malloc(sizeof(Camera));
    if (game->camera == NULL) {
        SDL_Log("error allocating camera");
        return false;
    }
    init_camera(game, game->window_size.x, game->window_size.y);
    game->world = create_world(game);
    if (game->world == NULL) {
        SDL_Log("error initializing world");
        return false;
    }
    game->running = true;
    game->last_frame_time = 0;
    game->target_frame_time = 16;
    game->vsync = true;

    SDL_Log("game initialized");
    return true;
}

void main_loop(Game *game) {
    Uint64 frame_start, sleep_time;
    char buffer[21];

    while (game->running) {
        frame_start = SDL_GetTicks();
        const InputState *input = ecs_singleton_get(game->world, InputState);
        if (input && input->quit) {
            game->running = false;
        }

        // game update
        tick(game);

        game->fps++;
        game->delta_time = SDL_GetTicks() - frame_start;

        // vsync
        if (game->vsync && game->delta_time < game->target_frame_time) {
            sleep_time = game->target_frame_time - game->delta_time;
            SDL_Delay(sleep_time);
        } else {
            sleep_time = 0;
        }

        if (frame_start > game->last_frame_time + 1000) {
            game->last_frame_time = frame_start;
            snprintf(buffer, sizeof(buffer), "%" PRIu64, game->fps);
            SDL_Log("FPS: %s\n", buffer);
            game->fps = 0;
        }
    }
};

void tick(Game *game) {
    update(game);
    render(game);
}

void update(Game *game) { ecs_progress(game->world, game->delta_time); }

void render(Game *game) {
    SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(game->renderer);

    handle_collisions(game->world, game);

    draw_sprites(game->world, game->renderer);
    draw_ui_sprites(game->world, game->renderer);

    SDL_RenderPresent(game->renderer);
}

void exit_application(Game *game) {
    ecs_query_t *query = ecs_query(game->world, {.terms = {{ecs_id(Sprite)}}});

    ecs_iter_t it = ecs_query_iter(game->world, query);
    while (ecs_query_next(&it)) {
        Sprite *sprites = ecs_field(&it, Sprite, 0);

        for (int i = 0; i < it.count; i++) {
            SDL_DestroyTexture(sprites[i].texture);
        }
    }
    ecs_fini(game->world);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);

    if (game->camera) {
        free(game->camera);
        game->camera = NULL;
    }

    SDL_Quit();
    SDL_Log("quit");
};

void init_camera(Game *game, int w, int h) {
    game->camera->x = 0;
    game->camera->y = 0;
    game->camera->zoom = 1.0f;
    game->camera->viewport = (SDL_FRect){0, 0, w, h};
}
