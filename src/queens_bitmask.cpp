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

    bitboard safe_bits = (bitboard)full_mask & ~(board.cols | board.diag1 | board.diag2);

    while (safe_bits > 0) {
        // 2. Extract the lowest set bit (find the first available position)
        bitboard bit = safe_bits & -safe_bits;

        // 3. Remove the chosen bit from the available positions
        safe_bits ^= bit;

        // 4. Prepare the board state for the next row
        Board next_board = board;
        
        // Mark the column as occupied
        next_board.cols = board.cols | bit;
        
        // KEY: Update diagonal masks for the next row
        // Left diagonals move one position to the left (left shift)
        next_board.diag1 = (board.diag1 | bit) << 1;
        
        // Right diagonals move one position to the right (right shift)
        next_board.diag2 = (board.diag2 | bit) >> 1;

        // 5. Recurse to the next row
        solve(row + 1, next_board, full_mask, count);
    }
    
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