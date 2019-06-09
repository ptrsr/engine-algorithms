cmake_minimum_required(VERSION 3.0)

## BUILDING
# package all source files in a library
# (for linking to both game and testing exe)
add_library(engine 
	glm.hpp

	input/file.cpp
	input/model.cpp

	auxiliary/c_getopt.h
	auxiliary/options.cpp

	core/engine.cpp
	core/system.cpp
	
	core/gpu/gpumodel.cpp
	core/gpu/gpuprogram.cpp
	core/gpu/shader.cpp

	components/transform.cpp
	components/hierarchy.cpp
	components/projection.cpp
	components/window.cpp
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
