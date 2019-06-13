#include "renderer.hpp"

#include <engine/glm.hpp>
#include <engine/core/scene.hpp>

#include <engine/entities/camera.hpp>
#include <engine/entities/renderobject.hpp>

#include <engine/components/material.hpp>
#include <engine/components/hierarchy.hpp>
#include <engine/components/transform.hpp>

glm::mat4 GetModelMatrix(GameObject& object) {
    Hierarchy* const parent_node = object.hierarchy.GetParent();

    if (!parent_node) {
        return object.transform;
    }
    GameObject& parent = *static_cast<GameObject*>(parent_node->entity);
    return object.transform * GetModelMatrix(parent);
}

void Renderer::Update(UpdateContext& context) {
    Camera& camera = *context.scene.GetEntity<Camera>();

    glm::mat4 view = GetModelMatrix(camera);
    glm::mat4 projection = camera.projection.perspective;
    
    std::vector<RenderObject*> render_objects = context.scene.GetEntities<RenderObject>();

    for (RenderObject* object : render_objects) {
        object->material.Use();

        glm::mat4 model = GetModelMatrix(*object);
        glm::mat4 mvp = model * view * projection;

        
    }
}
