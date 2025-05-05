cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SparseMatrix VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the executable
add_executable(main src/main.cpp)

# Enable testing
enable_testing()

# Add each test directory dynamically
file(GLOB TEST_DIRS RELATIVE ${CMAKE_SOURCE_DIR}/tests ${CMAKE_SOURCE_DIR}/tests/*)

foreach(TEST_NAME IN LISTS TEST_DIRS)
    if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/tests/${TEST_NAME}")
        add_executable(${TEST_NAME} ${CMAKE_SOURCE_DIR}/tests/${TEST_NAME}/main.cpp)
        target_include_directories(${TEST_NAME} PRIVATE include)
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endif()
endforeach()