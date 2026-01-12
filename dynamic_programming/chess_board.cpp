// Given an N*N matrix, what are the total number of ways in which we can move from the top-left cell
// o the bottom right cell, given we can move only either downward/rightward.

#include <iostream>
#include <array>

#define SZ 4

int ways = 0;
std::array< std::array<int, SZ>, SZ> memory; 
unsigned long TopL2BottomR(int N,  int rn, int cn) {
    if((rn == N-1 && cn == N-1) || (cn == N-1) || (rn == N-1)){
        return 1;
    }
    int next_row;
    int next_col;
    unsigned long down_ways;
    unsigned long right_ways;

    if(memory[rn][cn]) return memory[rn][cn];
    down_ways  = TopL2BottomR(N, rn+1, cn);
    right_ways = TopL2BottomR(N, rn, cn+1);
    memory[rn][cn] = down_ways + right_ways;
    return down_ways + right_ways;
}

unsigned long TopL2BottomR_iterative(int N, int rn, int cn){
    return 0;
}

int main(){
    for(int i = 0; i < SZ; ++i){
        memory[i].fill(0);
    }

    std::cout << "The ways to increment the knight is: " << TopL2BottomR(SZ, 0, 0) << '\n';
    
}
