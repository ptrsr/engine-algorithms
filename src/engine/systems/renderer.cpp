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

}

glm::mat4 GetModelMatrix(GameObject& object) {
    Hierarchy* const parent_node = object.hierarchy.GetParent();

    if (!parent_node) {
        return object.transform;
    }
    GameObject& parent = *static_cast<GameObject*>(parent_node->entity);
    return object.transform * GetModelMatrix(parent);
}

void Renderer::Update(UpdateContext& context) {

    Window& window = context.scene.GetEntity<Display>()->window;
    RenderObject& object = *context.scene.GetEntity<RenderObject>();

    std::vector<float> verts = { -0.6f, -0.4f, 1.f, 0.f, 0.f,
       0.6f, -0.4f, 0.f, 1.f, 0.f,
        0.f,  0.6f, 0.f, 0.f, 1.f };

    Buffer<float> buffer(verts, GL_ARRAY_BUFFER, 2, false);

    GLint mvp_location, vpos_location, vcol_location;
    mvp_location  = object.material.GetUniform("MVP");
    vpos_location = object.material.GetAttribute("vPos");
    vcol_location = object.material.GetAttribute("vCol");

    buffer.Bind(vpos_location, 2, sizeof(float) * 5);
    buffer.Bind(vcol_location, 3, sizeof(float) * 5, (void*) (sizeof(float) * 2));

    float ratio;
    int width, height;

    glfwGetFramebufferSize(window.context.get(), &width, &height);
    ratio = width / (float) height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 m(1);
    
    object.material.Use();
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(m));
    glDrawArrays(GL_TRIANGLES, 0, 3);

    window.SwapBuffer();

    buffer.UnBind(vpos_location);
    buffer.UnBind(vcol_location);

    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Display& display = *context.scene.GetEntity<Display>();
    // glm::vec2 buffer_size = display.window.GetFrameBufferSize();

    // Camera& camera = *context.scene.GetEntity<Camera>();

    // glm::mat4 view = GetModelMatrix(camera);
    // glm::mat4 projection = camera.projection.perspective;
    
    // std::vector<RenderObject*> render_objects = context.scene.GetEntities<RenderObject>();

    // glViewport(0, 0, 1280, 720);
    // glClear(GL_COLOR_BUFFER_BIT);

    // for (RenderObject* object : render_objects) {

    //     object->material.Use();

    //     glm::mat4 model = GetModelMatrix(*object);
    //     glm::mat4 mvp = projection * view * model;


    //     glm::ortho(-2, 2, -2 )
    //     glUniformMatrix4fv(object->material.GetUniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));


    //     object->mesh.vertex_buffer.Bind(object->material.GetAttribute("vertex"));
    //     object->mesh.normal_buffer.Bind(object->material.GetAttribute("normal"));
    //     object->mesh.uv_buffer.Bind(object->material.GetAttribute("uv"));
    //     object->mesh.index_buffer.Bind(0);

    //     glDrawElements(GL_TRIANGLES, object->mesh.index_buffer.size, GL_UNSIGNED_INT, (GLvoid*)0);

	//     glBindBuffer(GL_ARRAY_BUFFER, 0);
        
    //     object->mesh.vertex_buffer.UnBind();
    //     object->mesh.normal_buffer.UnBind();
    //     object->mesh.uv_buffer.UnBind();
    // }

    //display.window.SwapBuffer();
}
