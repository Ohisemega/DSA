#include <iostream>
#include <vector>

// std::vector
// our values and cap arrays begin with a dummy value so we have an array size of n+1 for n items e.g. value = {NULL, 4, 7, 2, ..., Vn}
// where "NULL" represents our dummy value
int Naive_01KnapSack_sol(int index, int capacity, std::vector<int>& value, std::vector<int>& cap){
    if(index == 0 || capacity == 0){
        return 0;
    }else if(cap[index] > capacity){
        return Naive_01KnapSack_sol(index - 1, capacity, value, cap);
    }else{
        return std::max(Naive_01KnapSack_sol(index - 1, capacity, value, cap), \
                        value[index] + Naive_01KnapSack_sol(index-1, capacity-cap[index], value, cap));
    }
}