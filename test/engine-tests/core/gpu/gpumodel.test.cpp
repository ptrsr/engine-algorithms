#include <gtest/gtest.h>

#include <engine/core/gpu/gpumodel.hpp>

#include <glbinding/glbinding.h>

#include <ostream>

#include <SFML/Window.hpp>

TEST(GpuModelTest, GenerateBuffer) {
    GpuModel model = GpuModel();

    std::vector<unsigned int> data = { 1, 2, 3, 4, 5, 6, 7, 8 };

    std::cout << data[2] << std::endl;

    sf::Window window(sf::VideoMode(800, 600), "OpenGL");

    gl::GLuint test = model.GenerateBuffer(data, gl::GL_ELEMENT_ARRAY_BUFFER);

    std::cout << test << std::endl;
}
