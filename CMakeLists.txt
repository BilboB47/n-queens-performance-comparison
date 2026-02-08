cmake_minimum_required(VERSION 3.18)
project(NQueensPerformance LANGUAGES CXX CUDA)

# --- Project Standards ---
# Use C++17 standard for modern features and CUDA compatibility
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Optimization Flags ---
# -O3 flag tells the compiler to optimize for maximum performance
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# --- CUDA Configuration ---
# Target architecture 61 is specific for NVIDIA Pascal GPUs (e.g., GTX 1050 Ti)
set(CMAKE_CUDA_ARCHITECTURES 61)
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -O3")

# --- Executables Definition ---
# Define output binaries and their corresponding source files in src/ directory
add_executable(queens_naive src/queens_naive.cpp)
add_executable(queens_bitmask src/queens_bitmask.cpp)
add_executable(queens_cuda src/queens_cuda.cu)

# --- Status Messages ---
# Print configuration status for the developer
message(STATUS "CUDA Architecture set to: ${CMAKE_CUDA_ARCHITECTURES}")
message(STATUS "Build type is set to Release with -O3 optimization")