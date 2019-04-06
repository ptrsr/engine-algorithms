include_directories(./)

list(APPEND SOURCES
	config.hpp

	mge/auxiliary/Hex.cpp
	mge/auxiliary/octree/Ball.cpp
	mge/auxiliary/octree/OcNode.cpp
	
	mge/behaviours/AbstractBehaviour.cpp
	mge/behaviours/AbstractLight.cpp
	mge/behaviours/CameraBehaviour.cpp
	mge/behaviours/DirectionalLight.cpp
	mge/behaviours/KeysBehaviour.cpp
	mge/behaviours/LookAt.cpp
	mge/behaviours/OrbitBehaviour.cpp
	mge/behaviours/PointLight.cpp
	mge/behaviours/RotatingBehaviour.cpp
	mge/behaviours/SpotLight.cpp

	
	mge/core/AbstractGame.cpp
	mge/core/Camera.cpp
	mge/core/GameObject.cpp
	mge/core/Mesh.cpp
	mge/core/Renderer.cpp
	mge/core/ShaderProgram.cpp
	mge/core/Texture.cpp
	mge/core/World.cpp
	
	mge/materials/AbstractMaterial.cpp
	mge/materials/ColorMaterial.cpp
	mge/materials/LitMaterial.cpp
	
	mge/scenes/OctreeScene.cpp
	
	mge/util/DebugHud.cpp
	mge/util/InputHandler.cpp
)

# -------------------------- Threading
# Multithreading support library
if(UNIX)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
	set (THREADING Threads::Threads)
endif()


# ========================== Building =========================== #

# ----------------------- engine-algorithms

include_directories(
	${GLEW_INCLUDE_DIR}
	${GLFW_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${SFML_INCLUDE_DIR}
)

add_executable(engine-algorithms main.cpp
	glm.hpp
	${SOURCES}
)
target_link_libraries(engine-algorithms 
	${GLEW_LIBS}
	${GLFW_LIBS}
	${SFML_LIBS}
)

set_target_properties(engine-algorithms PROPERTIES DEBUG_POSTFIX "-debug")
target_compile_options(engine-algorithms PRIVATE ${COMPILE_OPTS})


# =========================== Export ============================ #
# Testing requires the testing executable to know the
# full paths to the LOC3D_CPP files

# Macro for converting list with local paths to full paths
macro(ListToAbsolute REL_LIST REAL_LIST)
	foreach(REL IN LISTS ${REL_LIST})
		get_filename_component(REAL "${REL}"
                       REALPATH BASE_DIR)
	    list(APPEND ${REAL_LIST} ${REAL})
	endforeach(REL)
endmacro()

# Convert LOC3D_CPP local paths to global
# and export to upper CMakeLists

#ListToAbsolute(LOC3D_CPP ABS_FILES)
#set (TEST_FILES ${ABS_FILES} PARENT_SCOPE)
#set (TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)