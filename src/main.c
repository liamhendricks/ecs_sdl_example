#include <SDL3/SDL.h>
#include <core/game.h>
#include <ecs/components/input.h>
#include <ecs/systems/input.h>
#include <flecs.h>

int main() {
    Game game;

    bool ok = init_application(&game);
    if (ok) {
        main_loop(&game);
    }
    exit_application(&game);

    return 0;
}
