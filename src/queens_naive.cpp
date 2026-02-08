#include <iostream>
#include <vector>
#include <string>
#include <chrono>



struct Board {
    int n;
    std::vector<bool> cols;   
    std::vector<bool> diag1;  // backward (row - col)  ////
    std::vector<bool> diag2;  // forward (row + col)   \\\\

    // Inicjant size of Board
    Board(int size) : n(size), cols(size, false), 
                      diag1(2 * size - 1, false), 
                      diag2(2 * size - 1, false) {}
};




void solve(int row, Board& board, long long& count){
    
    if(row==board.n){
        count++;
        return;
    }

    for (int col = 0; col < board.n; col++) {

        int d1_idx = row - col + (board.n - 1); //offset to avoid negativ numbers
        int d2_idx = row + col;                 

        if (!board.cols[col] && !board.diag1[d1_idx] && !board.diag2[d2_idx]) {
            
            board.cols[col] = true;
            board.diag1[d1_idx] = true;
            board.diag2[d2_idx] = true;

            solve(row + 1, board, count);

            board.cols[col] = false;
            board.diag1[d1_idx] = false;
            board.diag2[d2_idx] = false;
        }
    }

}



int main(int argc, char** argv) {

    int n = (argc > 1) ? std::stoi(argv[1]) : 8;
    
    Board board(n);
    long long count = 0;

    auto start = std::chrono::high_resolution_clock::now();

    solve(0, board, count);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Format: N, Solutions, Time
    std::cout << n << "," << count << "," << duration.count() << std::endl;

    return 0;
}