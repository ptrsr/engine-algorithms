#include "game.hpp"

#include <engine/input/file.hpp>
#include <engine/input/model.hpp>

#include <engine/input/options.hpp>

#include <engine/entities/display.hpp>
#include <engine/entities/renderobject.hpp>
#include <engine/entities/camera.hpp>

#include <engine/components/mesh.hpp>
#include <engine/components/materials/meshmaterial.hpp>

#include <engine/systems/meshrenderer.hpp>
#include <engine/systems/refresher.hpp>
#include <engine/systems/octree.hpp>

#include <iostream>


Game::Game(const Options& options) {
    scene->AddEntity<Display>();

    // load model
    Model_ptr model = Model::FromOBJ(File(options.resource_dir + "teapot_smooth.obj"));
    
    // create material and mesh
    auto material = SharedComponent::Make<MeshMaterial>(options.resource_dir + "renderobjects/cube/cube");
    Mesh_ptr mesh = SharedComponent::Make<Mesh>(model);

    // create 3D object
    RenderObject& object = scene->AddEntity<RenderObject>(material, mesh);
    //object.transform.Scale(glm::vec3(0.001));

    // create camera
    Camera& camera = scene->AddEntity<Camera>(glm::radians(60.f), glm::vec2(1280, 720), 0.5f, 100);

    camera.transform.Translate(glm::vec3(0, 0, -3));

    // add render system
    AddSystem<MeshRenderer>();
    AddSystem<Refresher>();
    //AddSystem<OcTree>(options);
}
