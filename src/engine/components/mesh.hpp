#ifndef MESH_HPP_
#define MESH_HPP_

#include <engine/core/component.hpp>

#include <memory>

class GpuModel;
typedef std::shared_ptr<GpuModel> GpuModel_ptr;

class Mesh : public Component {
public:
	GpuModel_ptr   gpu_model;

	Mesh(GpuModel_ptr, gpu_model)
		: gpu_model(gpu_model)
		{ }

};

#endif//MESH_HPP_
