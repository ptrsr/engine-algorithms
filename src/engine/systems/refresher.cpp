#include "refresher.hpp"

#include <engine/core/scene.hpp>

#include <engine/components/window.hpp>
#include <engine/components/projection.hpp>

#include <engine/entities/display.hpp>
#include <engine/entities/camera.hpp>

#include <glbinding/gl/gl.h>

using namespace gl;

void Refresher::UpdateScreenSize(Projection& projection, const Window& window) const {
    glm::vec2 size = window.GetFrameBufferSize();
    
    // update viewport and projection matrix on window size change
    if (projection.GetWindowSize() != size) {
        projection.SetWindowSize(size);
        glViewport(0, 0, size.x, size.y);
    }
}

void Refresher::Update(UpdateContext& context) {
    // show last buffer on screen
    context.scene.GetEntity<Display>()->window.SwapBuffer();

    // clear next buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // window resizing
    Window& window = context.scene.GetEntity<Display>()->window;
    Camera& camera = *context.scene.GetEntity<Camera>();
    UpdateScreenSize(camera.projection, window);
}
