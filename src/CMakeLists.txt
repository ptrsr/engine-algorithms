cmake_minimum_required(VERSION 3.0)

## INCLUDING
# headers
include_directories(./)

# dependency headers
include_directories(
	${GLBINDING_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${GLFW_INCLUDE_DIR}
	${GOOGLETEST_INCLUDE_DIR}
)

# build engine library
add_subdirectory(engine)

# build game executable
add_subdirectory(game)
