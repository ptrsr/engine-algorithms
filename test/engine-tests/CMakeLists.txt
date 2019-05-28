cmake_minimum_required(VERSION 3.0)

# add engine-tests folder
target_include_directories(tests PUBLIC ./)

# policy for converting local to global paths in target_sources
cmake_policy(SET CMP0076 NEW)

# specify source files
target_sources(tests
PUBLIC
	# tests are run in given order
	input/options.test.cpp

	core/scene.test.cpp
	core/typemap.test.cpp
	core/entity.test.cpp
	core/component.test.cpp
	core/system.test.cpp

	components/transform.test.cpp
    components/hierarchical.test.cpp
)
