#include "gui.h"

ECS_COMPONENT_DECLARE(UIElement);

void register_ui_element_component(ecs_world_t *world) {
    ECS_COMPONENT_DEFINE(world, UIElement);
}
