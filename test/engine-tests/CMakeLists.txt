cmake_minimum_required(VERSION 3.0)

# add engine-tests folder
target_include_directories(tests PUBLIC ./)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.13.0")
	# policy for converting local to global paths in target_sources
	cmake_policy(SET CMP0076 OLD)
endif()

# specify source files
target_sources(tests
PUBLIC
	# tests are run in given order
	engine-tests/input/file.test.cpp
	engine-tests/input/options.test.cpp
	engine-tests/input/model.test.cpp

	engine-tests/core/scene.test.cpp
	engine-tests/core/typemap.test.cpp
	engine-tests/core/entity.test.cpp
	engine-tests/core/component.test.cpp
	engine-tests/core/system.test.cpp

	engine-tests/components/transform.test.cpp
	engine-tests/components/hierarchy.test.cpp
	engine-tests/components/projection.test.cpp
	engine-tests/components/mesh.test.cpp
	engine-tests/components/material.test.cpp
	
	engine-tests/entities/camera.test.cpp
)
