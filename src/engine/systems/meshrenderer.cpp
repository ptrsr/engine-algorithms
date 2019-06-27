#include "meshrenderer.hpp"

#include <engine/core/scene.hpp>

#include <engine/entities/renderobject.hpp>
#include <engine/entities/profiler.hpp>
#include <engine/entities/camera.hpp>
#include <engine/entities/display.hpp>

#include <engine/components/hierarchy.hpp>
#include <engine/components/transform.hpp>
#include <engine/components/materials/meshmaterial.hpp>
#include <engine/components/mesh.hpp>

#include <iostream>

#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>

using namespace gl;


glm::mat4 MeshRenderer::GetModelMatrix(GameObject& object) const {
    Hierarchy* const parent_node = object.hierarchy.GetParent();

    if (!parent_node) {
        return object.transform;
    }
    GameObject& parent = *static_cast<GameObject*>(parent_node->entity);
    return object.transform * GetModelMatrix(parent);
}

void MeshRenderer::Render(const RenderObject& object, const Camera& camera, const int mvp_id) const {
    // set model view projection uniform in shader
    glm::mat4 mvp = camera.projection.GetPerspective() * camera.transform * object.transform;
    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, glm::value_ptr(mvp));
    
    // draw polygons
    glDrawElements(GL_TRIANGLES, object.mesh.index_buffer.size, GL_UNSIGNED_INT, (GLvoid*)0);
}

void MeshRenderer::Update(UpdateContext& context) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // default GL_BACK
    
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT, GL_FILL);
    }

    Profiler& profiler = *context.scene.GetEntity<Profiler>();
    TimeTracker tracker = profiler.timer.Start("MeshRenderer");

    Camera& camera = *context.scene.GetEntity<Camera>();

    std::vector<RenderObject*> render_objects = context.scene.GetEntities<RenderObject>();
    
    for (RenderObject* object : render_objects) {
        object->material.Use();
        object->material.Bind(object->mesh);

        // set model view projection in shader
        glm::mat4 mvp = camera.projection.GetPerspective() * camera.transform * object->transform;
        glUniformMatrix4fv(object->material.mvp_uniform, 1, GL_FALSE, glm::value_ptr(mvp));

        glUniform3fv(object->material.color_uniform, 1, glm::value_ptr(glm::vec3(1, 0, 0)));

        glDrawElements(GL_POLYGON, object->mesh.index_buffer.size, GL_UNSIGNED_INT, (GLvoid*)0);

        object->material.UnBind();
    }

    profiler.timer.Stop(tracker);
}
