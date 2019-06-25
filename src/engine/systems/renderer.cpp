#include "renderer.hpp"

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


Renderer::Renderer() {
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE); // default GL_BACK
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

glm::mat4 Renderer::GetModelMatrix(GameObject& object) const {
    Hierarchy* const parent_node = object.hierarchy.GetParent();

    if (!parent_node) {
        return object.transform;
    }
    GameObject& parent = *static_cast<GameObject*>(parent_node->entity);
    return object.transform * GetModelMatrix(parent);
}

void UpdateScreenSize(Projection& projection, Window& window) {
    glm::vec2 size = window.GetFrameBufferSize();
    
    // update viewport and projection matrix on window size change
    if (projection.GetWindowSize() != size) {
        projection.SetWindowSize(size);
        glViewport(0, 0, size.x, size.y);
    }
}

void Renderer::Render(const RenderObject& object, const Camera& camera, const int mvp_id) const {
    // set model view projection uniform in shader
    glm::mat4 mvp = camera.projection.GetPerspective() * camera.transform * object.transform;
    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, glm::value_ptr(mvp));
    
    // draw polygons
    glDrawElements(GL_TRIANGLES, object.mesh.index_buffer.size, GL_UNSIGNED_INT, (GLvoid*)0);
}

void Renderer::Update(UpdateContext& context) {
    Profiler& profiler = *context.scene.GetEntity<Profiler>();
    TimeTracker tracker = profiler.timer.Start("Renderer");

    Window& window = context.scene.GetEntity<Display>()->window;
    Camera& camera = *context.scene.GetEntity<Camera>();

    // window resizing
    UpdateScreenSize(camera.projection, window);

    // clear draw buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::vector<RenderObject*> render_objects = context.scene.GetEntities<RenderObject>();
    
    for (RenderObject* object : render_objects) {
        object->material.Use();
        object->material.Bind(object->mesh);

        // set model view projection in shader
        glm::mat4 mvp = camera.projection.GetPerspective() * camera.transform * object->transform;
        glUniformMatrix4fv(object->material.mvp_uniform, 1, GL_FALSE, glm::value_ptr(mvp));

        glUniform3fv(object->material.color_uniform, 1, glm::value_ptr(glm::vec3(1, 0, 0)));

        glDrawElements(GL_QUADS, object->mesh.index_buffer.size, GL_UNSIGNED_INT, (GLvoid*)0);

        object->material.UnBind();
    }
    profiler.timer.Stop(tracker);
}

void Renderer::LateUpdate(UpdateContext& context) {
    // display on screen
    context.scene.GetEntity<Display>()->window.SwapBuffer();
}
