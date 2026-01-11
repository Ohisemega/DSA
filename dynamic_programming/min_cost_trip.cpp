#include <iostream>
#include <array>

/** There are N stations in a route starting from 0 to N-1.
 *  A train moves from the first station - 0 to the last
 *  station - N-1 in only forward direction. The cost of 
 *  travelling between any two station is given by a 2D
 *  array. Find the minimum cost of traveling from station - X
 *  to station - Y where X<= Y.
 */

#define MAX 4

int minCost_rec(int start, int end, std::array<std::array<int, MAX>, MAX> cost_mat){
    if(start == end-1 || start == end){
        return cost_mat[start][end];
    }
    
    int min_cost = cost_mat[start][end];
    for(int i = start+1; i < end; ++i){
        int stop_over_cost = minCost_rec(start, i, cost_mat) + minCost_rec(i, end, cost_mat);
        if(stop_over_cost < min_cost){
            min_cost = stop_over_cost;
        }
    }


    return min_cost; // placeholder 
}
