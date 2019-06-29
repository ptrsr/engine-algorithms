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
#include <engine/systems/simulator.hpp>

#include <engine/auxiliary/cube.hpp>


Game::Game(const Options& options) {
    scene->AddEntity<Display>();

    // create camera
    Camera& camera = scene->AddEntity<Camera>(glm::radians(60.f), glm::vec2(1280, 720), 0.5f, 100);
    camera.transform.Translate(glm::vec3(0, -.25f, -2));

    auto flat_material = SharedComponent::Make<MeshMaterial>(options.resource_dir + "shaders/flat_color");
    
    { // octree
        auto wire_cube_mesh = SharedComponent::Make<Mesh>(std::make_shared<Cube>());
        RenderObject& wire_cube = scene->AddEntity<RenderObject>(flat_material, wire_cube_mesh);
        
        AddSystem<OcTree>(wire_cube);
    }
    { // simulator
        auto cube_mesh = SharedComponent::Make<Mesh>(options.resource_dir + "models/cube");
        auto sphere_mesh = SharedComponent::Make<Mesh>(options.resource_dir + "models/sphere");

        SimulatorContext context(options.seed);
        context.dynamic_objects = 10;

        AddSystem<Simulator>(*scene, cube_mesh, sphere_mesh, flat_material, context);
    }

    AddSystem<MeshRenderer>();
    AddSystem<Refresher>();
}
