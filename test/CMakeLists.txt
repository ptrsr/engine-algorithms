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

	core/object.test.cpp
	core/world.test.cpp
	core/camera.test.cpp

	core/messages/world-message.test.cpp
)

target_link_libraries(test-engine framework)

#Multithreading library
if(UNIX)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
	set (THREADING Threads::Threads)
endif()

message(${CMAKE_BINARY_DIR})
find_library(FRAMEWORK libframework
PATHS ${CMAKE_BINARY_DIR}/src/libframework.a
)
message(${FRAMEWORK})


add_dependencies(test-engine googletest framework)

set_target_properties(test-engine
	PROPERTIES DEBUG_POSTFIX "-d"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin
)



target_link_libraries(test-engine 
    ${GOOGLETEST_LIBS}
    ${THREADING}
)
