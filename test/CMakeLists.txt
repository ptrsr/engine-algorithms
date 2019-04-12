cmake_minimum_required(VERSION 3.0)

include_directories(
    ./
    ../src/
    ${GOOGLETEST_INCLUDE_DIR}
)

add_executable(test-engine
	# tests
	engine-algorithms.test.cpp
	options.test.cpp
)

#Multithreading library
if(UNIX)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
	set (THREADING Threads::Threads)
endif()

add_dependencies(test-engine googletest)

set_target_properties(test-engine
	PROPERTIES DEBUG_POSTFIX "-d"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin
)
target_link_libraries(test-engine framework
    ${GOOGLETEST_LIBS}
    ${THREADING}
)
