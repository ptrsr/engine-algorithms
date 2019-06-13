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

using namespace gl;

Renderer::Renderer() {
    // glViewport(0, 0, 1280, 720);
    // glEnable( GL_DEPTH_TEST );
	// glEnable( GL_CULL_FACE ); // default GL_BACK
    // glEnable (GL_BLEND);
    // glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glClearColor((float)0x2d/0xff, (float)0x6b/0xff, (float)0xce/0xff, 1.0f );
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Display& display = *context.scene.GetEntity<Display>();
    glm::vec2 buffer_size = display.window.GetFrameBufferSize();

    Camera& camera = *context.scene.GetEntity<Camera>();

    glm::mat4 view = GetModelMatrix(camera);
    glm::mat4 projection = camera.projection.perspective;
    
    std::vector<RenderObject*> render_objects = context.scene.GetEntities<RenderObject>();

    glViewport(0, 0, 1280, 720);
    glClear(GL_COLOR_BUFFER_BIT);

    for (RenderObject* object : render_objects) {

        object->material.Use();

        glm::mat4 model = GetModelMatrix(*object);
        glm::mat4 mvp = projection * view * model;


        
        glUniformMatrix4fv(object->material.GetUniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));


        object->mesh.vertex_buffer.Bind(object->material.GetAttribute("vertex"));
        object->mesh.normal_buffer.Bind(object->material.GetAttribute("normal"));
        object->mesh.uv_buffer.Bind(object->material.GetAttribute("uv"));
        object->mesh.index_buffer.Bind(0);

        glDrawElements(GL_TRIANGLES, object->mesh.index_buffer.size, GL_UNSIGNED_INT, (GLvoid*)0);

	    glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        object->mesh.vertex_buffer.UnBind();
        object->mesh.normal_buffer.UnBind();
        object->mesh.uv_buffer.UnBind();
    }

    display.window.SwapBuffer();

    std::string test;
    std::cin >> test;
    std::cout << "ok" << std::endl;
}
