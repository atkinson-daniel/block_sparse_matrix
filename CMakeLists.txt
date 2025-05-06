cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SparseMatrix VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE DEBUG)

# Include directories
include_directories(include)

# Add the executable
add_executable(main src/main.cpp)