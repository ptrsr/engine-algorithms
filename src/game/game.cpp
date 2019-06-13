#include "game.hpp"

#include <engine/input/file.hpp>
#include <engine/input/model.hpp>

#include <engine/auxiliary/options.hpp>

#include <engine/entities/display.hpp>
#include <engine/entities/renderobject.hpp>

#include <engine/components/mesh.hpp>
#include <engine/components/material.hpp>

#include <engine/systems/renderer.hpp>


Game::Game() {
    std::string resources_dir = std::string(RESOURCE_DIR);

    scene->AddEntity<Display>();
    
    // load model
    File model_file(resources_dir + "test-model.obj");
    Model_ptr model = Model::FromOBJ(model_file.content);

    // load shaders
    File vert_file(resources_dir + "color.vs");
    File frag_file(resources_dir + "color.fs");

    Shaders shaders = {
        Shader(vert_file.content, Shader::vertex),
        Shader(frag_file.content, Shader::fragment)
    };
    
    // create material and mesh
    Material_ptr material = SharedComponent::Make<Material>(shaders);
    Mesh_ptr mesh = SharedComponent::Make<Mesh>(*model);

    // create 3D object
    RenderObject& object = scene->AddEntity<RenderObject>(material, mesh);

    // add render system
    AddSystem<Renderer>();
}
