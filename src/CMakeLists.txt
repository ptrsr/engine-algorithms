cmake_minimum_required(VERSION 3.0)

## INCLUDING
# framework headers
include_directories(./)

# dependency headers
include_directories(
	${GLBINDING_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${SFML_INCLUDE_DIR}
	${GOOGLETEST_INCLUDE_DIR}
)

# framework implementation
list(APPEND SOURCES
	glm.hpp

	auxiliary/c_getopt.h
	auxiliary/options.cpp

	core/world.cpp
	core/object.cpp
	#core/camera.cpp
)

## BUILDING
# package all source files in a library
# (for linking to both project and testing exe)
add_library(framework ${SOURCES})
add_dependencies(framework glbinding glm sfml)
set(FRAMEWORK framework PARENT_SCOPE)
# because the libraries do not exist during configuration time,
# preditermine the library language (to avoid a warning)
set_target_properties(framework PROPERTIES LINKER_LANGUAGE CXX)

# (glm is header only, no need to link)
target_link_libraries(framework ${GLBINDING_LIBS} ${GLM_LIBS} ${SFML_LIBS})

# build executable
add_executable(engine-algorithms engine-algorithms.cpp)
add_dependencies(engine-algorithms framework)
target_link_libraries(engine-algorithms framework)

set_target_properties(engine-algorithms 
	PROPERTIES DEBUG_POSTFIX "-d"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin
)
# target_compile_options(engine-algorithms PRIVATE ${COMPILE_OPTS})
