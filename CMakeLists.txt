cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SparseMatrix VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Try to Find GTest
find_package(GTest QUIET)

if(GTEST_FOUND)
	message(">> GTest was found among local libraries.")
	include_directories(${GTEST_INCLUDE_DIRS})

	# create an executable for all tests 
	add_executable( run_tests ${TEST_FILES} ${USER_FILES} )
	target_link_libraries( run_tests gtest_main ${GTEST_LIBRARIES} pthread)

else()
	message(">> Couldn't find Local GTest library, Downloading one instead ...")

	# Download and unpack googletest at configure time
	configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
	if(result)
		message(FATAL_ERROR "CMake step for googletest failed: ${result}")
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
	if(result)
		message(FATAL_ERROR "Build step for googletest failed: ${result}")
	endif()

	# Prevent overriding the parent project's compiler/linker
	# settings on Windows
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	# Add googletest directly to our build. This defines
	# the gtest and gtest_main targets.
	add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
		${CMAKE_CURRENT_BINARY_DIR}/googletest-build
	        EXCLUDE_FROM_ALL)

	# create an executable for all tests 
	add_executable( run_tests ${TEST_FILES} ${USER_FILES} )
	target_link_libraries( run_tests gtest_main)
endif()

ENABLE_TESTING()

# Include directories
include_directories(include)

# Add the executable
add_executable(main src/main.cpp)
