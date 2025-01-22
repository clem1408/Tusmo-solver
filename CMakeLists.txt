# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(Tusmo-solver LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set source file
set(SOURCE_FILE ${CMAKE_SOURCE_DIR}/src/generate.cpp)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/french_set)

# Output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add executable
add_executable(generate ${SOURCE_FILE})

# Ensure /french_set/ is accessible at runtime
configure_file(${CMAKE_SOURCE_DIR}/french_set/lst_mots.txt ${CMAKE_BINARY_DIR}/database.txt COPYONLY)

# Print a message to indicate build setup completion
message(STATUS "Build setup complete. The executable will be in the /build directory.")
