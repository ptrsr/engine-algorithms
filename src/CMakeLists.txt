cmake_minimum_required(VERSION 3.0)

# DECLARING
# framework headers
include_directories(./)

# dependency headers
include_directories(
	${GLBINDING_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${SFML_INCLUDE_DIR}
)

# framework implementation
list(APPEND SOURCES
	glm.hpp

	auxiliary/c_getopt.h
	auxiliary/options.hpp
)

## BUILDING
# package all source files in a library
# (for linking to both project and testing exe)
add_library(framework ${SOURCES})

# (wait for dependencies to be set up before continuing)
add_dependencies(framework glm sfml glbinding)
SET_TARGET_PROPERTIES(framework PROPERTIES LINKER_LANGUAGE CXX)

# (glm is header only, no need to link)
#target_link_libraries(framework ${GLEW_LIBS} ${GLFW_LIBS} ${SFML_LIBS})

# build executable
add_executable(engine-algorithms engine-algorithms.cpp)
add_dependencies(engine-algorithms framework)
target_link_libraries(engine-algorithms framework)

#target_link_libraries(engine-algorithms framework)

set_target_properties( engine-algorithms PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin 
	LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
	DEBUG_POSTFIX "-debug"
)
target_compile_options(engine-algorithms PRIVATE ${COMPILE_OPTS})



## EXPORT
# Testing requires the testing executable to know the
# full paths to the source files

# Macro for converting list with local paths to full paths
macro(ListToAbsolute REL_LIST REAL_LIST)
	foreach(REL IN LISTS ${REL_LIST})
		get_filename_component(REAL "${REL}"
                       REALPATH BASE_DIR)
	    list(APPEND ${REAL_LIST} ${REAL})
	endforeach(REL)
endmacro()

# Convert source local paths to global
# and export to upper CMakeLists

ListToAbsolute(SOURCES ABS_SOURCES)
#set (TEST_FILES ${ABS_FILES} PARENT_SCOPE)
#set (TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)