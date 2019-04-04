list(APPEND LIBS
	googletest 
	glew 
	glfw 
)

foreach(LIB ${LIBS})
	configure_file(CMakeLists.${LIB}.in ${CMAKE_SOURCE_DIR}/lib/${LIB}/config/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" ${CMAKE_SOURCE_DIR}/lib/${LIB}/config
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${LIB}/config )
	
	if(result)
		message(FATAL_ERROR "CMake step for ${LIB} failed: ${result}")
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} --build ${CMAKE_SOURCE_DIR}/lib/${LIB}/config
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${LIB}/config )
	if(result)
		message(FATAL_ERROR "Build step for ${LIB} failed: ${result}")
	endif()
endforeach(LIB)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Now simply link against gtest or gtest_main as needed. Eg
# include_directories(
# 	${AprilTags_HEADERS}
# 	${TEST_HEADERS}
# )

# add_executable(test_loc3d 
# 	# tests
# 	main_test.cpp
# 	settings_test.cpp
# 	quaternion_test.cpp 
# 	resource_loader_test.cpp
	
# 	# auxiliary files
# 	settings_aux.cpp
# 	float_aux.hpp
# 	vector_aux.hpp
# 	${TEST_FILES}
# )

# target_link_libraries(test_loc3d 
# 	gmock_main
# 	${OpenCV_LIBRARIES}
# 	${CGAL_LIBRARIES}
# 	${AprilTags_LIBRARIES}
# 	${Boost_LIBRARIES}
# )
# add_test(COMMAND test_loc3d)
