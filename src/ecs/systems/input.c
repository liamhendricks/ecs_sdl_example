#include "input.h"
#include "SDL3/SDL_log.h"
#include "core/game.h"
#include "ecs/components/input.h"
#include "ecs/components/position.h"
#include "flecs.h"
#include <SDL3/SDL.h>
#include <math.h>
#include <stdio.h>

const float CAMERA_SPEED = 3.0f;
const float SCREEN_MOVE_PERCENTAGE_X = 0.05f;
const float SCREEN_MOVE_PERCENTAGE_Y = 0.075f;
const Uint8 MOUSE_OFFSET = 16;

void InputSystem(ecs_iter_t *it) {
    InputState *input = ecs_singleton_get_mut(it->world, InputState);
    ecs_entity_t mid = ecs_lookup(it->world, "MouseCursor");
    Position *mouse_position = ecs_get_mut(it->world, mid, Position);
    ecs_entity_t pid = ecs_lookup(it->world, "Player");
    Position *player_position = ecs_get_mut(it->world, pid, Position);

    Game *game = ecs_get_ctx(it->world);
    if (game->camera == NULL) {
        SDL_Log("camera not initialized, exiting");
        game->running = false;
        return;
    }

    SDL_Event event;
    const bool *keystate = SDL_GetKeyboardState(NULL);

    input->quit = keystate[SDL_SCANCODE_CAPSLOCK];
    input->up = keystate[SDL_SCANCODE_W];
    input->down = keystate[SDL_SCANCODE_S];
    input->left = keystate[SDL_SCANCODE_A];
    input->right = keystate[SDL_SCANCODE_D];
    input->fire = keystate[SDL_SCANCODE_SPACE];
    input->mouse_l = false;
    input->mouse_r = false;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            input->quit = true;
        } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                input->mouse_l = true;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                input->mouse_r = true;
            }
        } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
            if (SDL_ConvertEventToRenderCoordinates(game->renderer, &event)) {
                input->mouse_pos.x = event.motion.x;
                input->mouse_pos.y = event.motion.y;
                mouse_position->x = roundf(input->mouse_pos.x - MOUSE_OFFSET);
                mouse_position->y = roundf(input->mouse_pos.y - MOUSE_OFFSET);
            }
        }
    }

    if (input->up) {
        move_position(player_position, 0.0f, -CAMERA_SPEED);
    }
    if (input->down) {
        move_position(player_position, 0.0f, CAMERA_SPEED);
    }
    if (input->right) {
        move_position(player_position, CAMERA_SPEED, 0.0f);
    }
    if (input->left) {
        move_position(player_position, -CAMERA_SPEED, 0.0f);
    }

    float x_per = game->window_size.x * SCREEN_MOVE_PERCENTAGE_X;
    float y_per = game->window_size.y * SCREEN_MOVE_PERCENTAGE_Y;

    if (mouse_position->x > (game->window_size.x - x_per) - MOUSE_OFFSET) {
        SDL_Log("RIGHT");
        move_camera(game->camera, CAMERA_SPEED, 0.0f);
    }

    if (mouse_position->x < (x_per - MOUSE_OFFSET)) {
        SDL_Log("LEFT");
        move_camera(game->camera, -CAMERA_SPEED, 0.0f);
    }

    if (mouse_position->y > (game->window_size.y - y_per) - MOUSE_OFFSET) {
        SDL_Log("DOWN");
        move_camera(game->camera, 0.0f, CAMERA_SPEED);
    }

    if (mouse_position->y < (y_per - MOUSE_OFFSET)) {
        SDL_Log("UP");
        move_camera(game->camera, 0.0f, -CAMERA_SPEED);
    }

    ecs_singleton_modified(it->world, InputState);
    ecs_modified(it->world, mid, Position);
    ecs_modified(it->world, pid, Position);
}
void register_input_system(ecs_world_t *world, Game *game) {
    ECS_SYSTEM(world, InputSystem, EcsPreUpdate, 0);
    ecs_set_ctx(world, game, NULL);
}

void move_camera(Camera *camera, float dx, float dy) {
    camera->x += roundf(dx);
    camera->y += roundf(dy);
    camera->viewport.x = camera->x;
    camera->viewport.y = camera->y;
}

void move_position(Position *position, float dx, float dy) {
    position->x += roundf(dx);
    position->y += roundf(dy);
}
