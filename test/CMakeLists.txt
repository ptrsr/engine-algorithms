cmake_minimum_required(VERSION 3.0)

include_directories(
    ../src/
	${GOOGLETEST_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${GLBINDING_INCLUDE_DIR}
	${SFML_INCLUDE_DIR}
)

# create tests executable
add_executable(tests main.test.cpp)

# wait for googletest before building tests
add_dependencies(tests googletest)

# define test resources
add_definitions(-DTEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test-resources/")

# add engine and game tests seperately
add_subdirectory(engine-tests)
add_subdirectory(game-tests)

# multithreading library
if(UNIX)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
	set (THREADING Threads::Threads)
endif()

# link tests exe to engine, google-test and multithreading
target_link_libraries(tests 
	engine
	${GOOGLETEST_LIBS}
	${THREADING}
	${SFML_LIBS}
)

set_target_properties(tests
	PROPERTIES DEBUG_POSTFIX "-d"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin
)
