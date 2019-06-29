#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

#include <engine/core/system.hpp>

class Mesh;
typedef std::shared_ptr<Mesh> Mesh_ptr;

class MeshMaterial;
typedef std::shared_ptr<MeshMaterial> MeshMaterial_ptr;

struct SimulatorContext {
    const int seed; 
    unsigned  static_objects; 
    unsigned  dynamic_objects;

    SimulatorContext(int seed = 0)
        : seed(seed)
        , static_objects(0)
        , dynamic_objects(0)
        { }
};

class Simulator : public System {
public:
    Simulator(Scene& scene, 
              Mesh_ptr& cube, 
              Mesh_ptr& sphere, 
              MeshMaterial_ptr& material, 
              const SimulatorContext& context);

    void Update(UpdateContext& context) override;
};

#endif//SIMULATOR_HPP_
