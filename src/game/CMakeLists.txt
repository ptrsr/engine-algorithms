cmake_minimum_required(VERSION 3.0)

add_compile_definitions(RESOURCE_DIR="${PROJECT_SOURCE_DIR}/resources/")

# create game executable
add_executable(game main.cpp
	game.cpp
)

# link game executable to engine library
target_link_libraries(game engine)

set_target_properties(game 
	PROPERTIES DEBUG_POSTFIX "-d"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin
)
