cmake_minimum_required(VERSION 3.0)

## BUILDING
# package all source files in a library
# (for linking to both game and testing exe)
add_library(engine 
	glm.hpp

	auxiliary/cgetopt.h

	input/model.cpp
	input/file.cpp
	input/options.cpp
	
	core/engine.cpp
	core/system.cpp
	
	components/projection.cpp
	components/transform.cpp
	components/hierarchy.cpp
	components/material.cpp
	components/collider.cpp
	components/window.cpp
	components/timer.cpp
	components/mesh.cpp

	components/materials/mesh-material.cpp
	
	components/colliders/sphere-collider.cpp
	components/colliders/alligned-box-collider.cpp

	entities/renderobject.cpp
	entities/gameobject.cpp

	systems/meshrenderer.cpp
	systems/simulator.cpp
	systems/refresher.cpp
	systems/octree.cpp
)
	
# wait for glm before building engine
add_dependencies(engine glm)

if (${BUILD_HEAD})
	add_dependencies(engine glbinding glfw)

	# do not include OpenGL functions from GLFW
	target_compile_definitions(engine PUBLIC GLFW_INCLUDE_NONE)
endif()

# because the libraries do not exist during configuration time,
# predetermine the library language (to avoid a warning)
set_target_properties(engine PROPERTIES LINKER_LANGUAGE CXX)

# NOTE: glm is header only, no need to link
target_link_libraries(engine 
	${GLBINDING_LIBS} 
	${GLFW_LIBS}
)
