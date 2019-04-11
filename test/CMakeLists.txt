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

target_link_libraries(test-engine framework
    ${GOOGLETEST_LIBS}
    ${THREADING}
)
