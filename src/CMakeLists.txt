# CMake configuration for src directory

add_executable(nbody_simulator main.cpp)

# Link CUDA kernel object
set(CUDA_KERNELS
    ${CMAKE_SOURCE_DIR}/cuda/hello_kernel.cu
)

set_source_files_properties(${CUDA_KERNELS} PROPERTIES LANGUAGE CUDA)
target_sources(nbody_simulator PRIVATE ${CUDA_KERNELS})

target_link_libraries(nbody_simulator PRIVATE cuda)
