#include <cuda_runtime.h>
#include <iostream>

// Kernel declaration
__global__ void hello();

int main() {
    hello<<<1, 8>>>();
    cudaError_t err = cudaDeviceSynchronize();
    if (err != cudaSuccess) {
        std::cerr << "CUDA error: " << cudaGetErrorString(err) << std::endl;
        return 1;
    }
    return 0;
}