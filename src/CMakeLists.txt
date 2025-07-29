# CMake configuration for src directory
# Make headers in include/ and src/barneshut/ available
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src/barneshut)

add_executable(nbody_simulator main.cpp)

# Link CUDA kernel object
set(CUDA_KERNELS
    ${CMAKE_SOURCE_DIR}/cuda/hello_kernel.cu
)

set_source_files_properties(${CUDA_KERNELS} PROPERTIES LANGUAGE CUDA)
target_sources(nbody_simulator PRIVATE ${CUDA_KERNELS})

target_link_libraries(nbody_simulator PRIVATE cuda)

# Barnes-Hut CPU implementation
set(BARNESHUT_SOURCES
    barneshut/ThreadPool.cpp
    barneshut/NodePool.cpp
    barneshut/BarnesHutTree.cpp
    barneshut/GraphvizDump.cpp
)
target_sources(nbody_simulator PRIVATE ${BARNESHUT_SOURCES})
  # Sanity check executable for Barnes–Hut tree
add_executable(sanity_check barneshut/sanity.cpp)
target_sources(sanity_check PRIVATE ${BARNESHUT_SOURCES})
target_link_libraries(sanity_check PRIVATE)
