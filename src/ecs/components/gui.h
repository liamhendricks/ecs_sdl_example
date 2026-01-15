#pragma onces

#include <flecs.h>

typedef struct {
    bool enabled;
} UIElement;

extern ECS_COMPONENT_DECLARE(UIElement);
void register_ui_element_component(ecs_world_t *world);
