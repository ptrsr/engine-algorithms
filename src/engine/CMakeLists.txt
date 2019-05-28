cmake_minimum_required(VERSION 3.0)

## BUILDING
# package all source files in a library
# (for linking to both game and testing exe)
add_library(engine 
	glm.hpp

	auxiliary/c_getopt.h
	auxiliary/options.cpp

	core/engine.cpp
	core/system.cpp

	components/transform.cpp
	components/hierarchical.cpp
)

add_dependencies(engine 
    glbinding 
    glm 
    sfml
)

# because the libraries do not exist during configuration time,
# predetermine the library language (to avoid a warning)
set_target_properties(engine PROPERTIES LINKER_LANGUAGE CXX)

# NOTE: glm is header only, no need to link
target_link_libraries(engine ${GLBINDING_LIBS} ${GLM_LIBS} ${SFML_LIBS})
