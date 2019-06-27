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

#include <engine/auxiliary/cube.hpp>

#include <iostream>


Game::Game(const Options& options) {
    scene->AddEntity<Display>();

    // create camera
    Camera& camera = scene->AddEntity<Camera>(glm::radians(60.f), glm::vec2(1280, 720), 0.5f, 100);
    camera.transform.Translate(glm::vec3(0, -.1f, -1));

    // cube
    auto mesh = SharedComponent::Make<Mesh>(std::make_shared<Cube>());
    auto mat = SharedComponent::Make<MeshMaterial>(options.resource_dir + "shaders/cube");
    RenderObject& cube = scene->AddEntity<RenderObject>(mat, mesh);

    // AddSystem<MeshRenderer>();
    AddSystem<OcTree>(cube);
    AddSystem<Refresher>();
}
