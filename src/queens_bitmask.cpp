#include <iostream>
#include <cstdint>
#include <string>
#include <chrono>




using bitboard = uint32_t;

struct Board {
    int n;
    bitboard cols;   
    bitboard diag1;  // backward (row - col)  ////
    bitboard diag2;  // forward (row + col)   \\\\
    
    Board(int size) : n(size), cols(0ULL), diag1(0ULL), diag2(0ULL) {}
};


void solve(int row, Board board, uint64_t full_mask, long long& count) {
    if (row == board.n) {
        count++;
        return;
    }

    //TODO
   
}



int main(int argc, char** argv) {
    int n = (argc > 1) ? std::stoi(argv[1]) : 8;
    
    uint64_t full_mask = (n == 64) ? ~0ULL : (1ULL << n) - 1;

    Board board(n); // Twoja nowa struktura bitowa
    long long count = 0;

    auto start = std::chrono::high_resolution_clock::now();

    solve(0, board, full_mask, count);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;


    std::cout << n << "," << count << "," << duration.count() << std::endl;
    return 0;
}