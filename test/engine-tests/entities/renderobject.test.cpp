#include <gtest/gtest.h>

#include <engine/entities/renderobject.hpp>

#include <engine/components/materials/meshmaterial.hpp>
#include <engine/components/mesh.hpp>


TEST(RenderObject, Constructor) {
    RenderObject object = RenderObject(0, std::string(TEST_RESOURCE_DIR) + "cube");

    ASSERT_NE(-1, object.material.GetUniform("mvp"));
    ASSERT_NE(0, object.mesh.vertex_buffer.id);
}
