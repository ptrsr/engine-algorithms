cmake_minimum_required(VERSION 3.0)

include_directories(
    ./
    ../src/
	${GOOGLETEST_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
)

add_executable(test-engine engine-algorithms.test.cpp
	# tests are run in following order
	input/options.test.cpp

	core/engine.test.cpp

	#core/world.test.cpp
	#core/object.test.cpp
	#core/camera.test.cpp
)

target_link_libraries(test-engine engine)

# multithreading library
if(UNIX)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
	set (THREADING Threads::Threads)
endif()

# TODO: already done using target_link_libraries (?)
add_dependencies(test-engine engine googletest)

set_target_properties(test-engine
	PROPERTIES DEBUG_POSTFIX "-d"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin
)

target_link_libraries(test-engine 
    ${GOOGLETEST_LIBS}
    ${THREADING}
)
