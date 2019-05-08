cmake_minimum_required(VERSION 3.0)

add_executable(algorithms algorithms.cpp)
add_dependencies(algorithms engine)
target_link_libraries(algorithms engine)

set_target_properties(engine 
	PROPERTIES DEBUG_POSTFIX "-d"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin
)
