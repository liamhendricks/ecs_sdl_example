cmake_minimum_required(VERSION 3.16)
project(ecs_sdl_example)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/flecs)

add_executable(ecs_sdl_example 
    src/main.c
    src/core/camera.c
    src/core/game.c
    src/core/tilemap.c
    src/core/world.c
    src/ecs/entities/player.c
    src/ecs/entities/gui/mouse.c
    src/ecs/components/collision.c
    src/ecs/components/input.c
    src/ecs/components/gui.c
    src/ecs/components/position.c
    src/ecs/components/sprite.c
    src/ecs/components/velocity.c
    src/ecs/systems/draw_sprite.c
    src/ecs/systems/draw_ui_sprite.c
    src/ecs/systems/collision.c
    src/ecs/systems/input.c
    src/ecs/systems/move.c
)

target_include_directories(ecs_sdl_example PRIVATE 
    includes
    src
    vendored/flecs/include
)

target_link_libraries(ecs_sdl_example PRIVATE 
    flecs::flecs_static 
    SDL3::SDL3
    m
)

target_compile_definitions(ecs_sdl_example PRIVATE 
    FLECS_C
    FLECS_NO_CPP
)
