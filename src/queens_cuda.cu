#include <iostream>
#include <cuda_runtime.h>
#include <chrono>
#include <cstdint>

typedef uint32_t bitboard;

/**
 * GPU Device function: recursive bitmask solver.
 * Each thread handles one branch of the state space.
 */
__device__ void solve_cuda(int row, int n, bitboard cols, bitboard ld, bitboard rd, bitboard full_mask, unsigned long long* global_count) {
    // Base case: All queens placed
    if (cols == full_mask) {
        atomicAdd(global_count, 1); // Safely increment the global counter across threads
        return;
    }

    // Identify safe positions in the current row
    bitboard safe_bits = full_mask & ~(cols | ld | rd);

    while (safe_bits > 0) {
        // Isolate the lowest set bit
        bitboard bit = safe_bits & -safe_bits;
        
        // Remove the bit from available positions
        safe_bits ^= bit;

        // Recurse to the next row with updated masks
        solve_cuda(row + 1, n, 
                   cols | bit, 
                   (ld | bit) << 1, 
                   (rd | bit) >> 1, 
                   full_mask, global_count);
    }
}

/**
 * CUDA Kernel: Entry point for the GPU.
 * Each thread starts with a queen placed in a different column of the first row.
 */
__global__ void queens_kernel(int n, bitboard full_mask, unsigned long long* d_count) {
    // Map thread ID to the starting column of the first row
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (col < n) {
        bitboard bit = (1 << col);
        // Start recursion from row 1 (the second row)
        solve_cuda(1, n, bit, bit << 1, bit >> 1, full_mask, d_count);
    }
}

int main(int argc, char** argv) {
    int n = (argc > 1) ? std::stoi(argv[1]) : 8;
    if (n < 1 || n > 32) return 1;

    bitboard full_mask = (1ULL << n) - 1;

    unsigned long long h_count = 0;
    unsigned long long* d_count;

    // Allocate memory on the GPU (Device)
    cudaMalloc(&d_count, sizeof(unsigned long long));
    cudaMemcpy(d_count, &h_count, sizeof(unsigned long long), cudaMemcpyHostToDevice);

    auto start = std::chrono::high_resolution_clock::now();

    // Launch the kernel: 1 block with N threads
    // Each thread starts a massive search tree from the first row
    queens_kernel<<<1, n>>>(n, full_mask, d_count);

    // Wait for GPU to finish
    cudaDeviceSynchronize();

    auto end = std::chrono::high_resolution_clock::now();
    
    // Copy the final count back to the CPU (Host)
    cudaMemcpy(&h_count, d_count, sizeof(unsigned long long), cudaMemcpyDeviceToHost);

    std::chrono::duration<double> duration = end - start;
    std::cout << n << "," << h_count << "," << duration.count() << std::endl;

    // Cleanup
    cudaFree(d_count);
    return 0;
}