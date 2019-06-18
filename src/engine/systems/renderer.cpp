#include "renderer.hpp"

#include <engine/glm.hpp>
#include <engine/core/scene.hpp>

#include <engine/entities/camera.hpp>
#include <engine/entities/renderobject.hpp>
#include <engine/entities/display.hpp>

#include <engine/components/material.hpp>
#include <engine/components/mesh.hpp>
#include <engine/components/hierarchy.hpp>
#include <engine/components/transform.hpp>

#include <iostream>

#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>

using namespace gl;


Renderer::Renderer() {
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE ); // default GL_BACK
}

glm::mat4 GetModelMatrix(GameObject& object) {
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
    Window& window = context.scene.GetEntity<Display>()->window;
    RenderObject& object = *context.scene.GetEntity<RenderObject>();
    Camera& camera = *context.scene.GetEntity<Camera>();

    object.transform.Rotate(0.01f, glm::vec3(0, 1, 0));

    // window resizing
    UpdateScreenSize(camera.projection, window);

    // clear draw buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLint vertex_id = object.material.GetAttribute("vertex");
    GLint normal_id = object.material.GetAttribute("normal");
    
    GLint mvp_id = object.material.GetUniform("mvp_mat");
    
    // TODO: temporary!
    GLint model_m_id = object.material.GetUniform("model_mat");
    glUniformMatrix4fv(model_m_id, 1, GL_FALSE, glm::value_ptr((glm::mat4)object.transform));

    // set gpu program
    object.material.Use();
    
    // bind buffers to gpu program
    object.mesh.vertex_buffer.Bind(vertex_id);
    object.mesh.normal_buffer.Bind(normal_id);

    object.mesh.index_buffer.Bind(0);

    Render(object, camera, mvp_id);

    // display on screen
    window.SwapBuffer();

    // unbind buffers from gpu program
    object.mesh.vertex_buffer.UnBind(vertex_id);
    object.mesh.normal_buffer.UnBind(normal_id);
}
