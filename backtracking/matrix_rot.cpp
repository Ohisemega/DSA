#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rotate(vector<vector<int>>& matrix) {
        // first transpose the graph
        // then reverse the columsn
        int sz = matrix.size(); // N x N matrix
        for(int i = 0; i < sz; ++i){
            for(int j = i+1; j < sz; ++j){
                std::cout << matrix[i][j] << ", " << matrix[j][i] << '\n';
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }

        for(int i = 0; i < sz; ++i){
            std::reverse(matrix[i].begin(), matrix[i].end());
        }
}


int main(){
    vector<vector<int>> vec{{1,2,3}, {4,5,6}, {7,8,9}};
    rotate(vec);
    for(int i = 0; i < vec.size(); ++i){
        for(int j = 0; j < vec.size(); ++j){
            std::cout << vec[i][j] << ' ';
        
        }
        std::cout << '\n';
    }
}
