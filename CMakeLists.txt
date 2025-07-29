cmake_minimum_required(VERSION 3.18)

project(CUDA_BarnesHut_NBodySimulator LANGUAGES CXX CUDA)
# Make headers in include/ available to all targets
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
add_subdirectory(src)
add_subdirectory(cuda)
add_subdirectory(tests)
