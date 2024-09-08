#include <iostream>
#include <vector>

// std::vector
// our values and cap arrays begin with a dummy value so we have an array size of n+1 for n items e.g. value = {NULL, 4, 7, 2, ..., Vn}
// where "NULL" represents our dummy value

/** 
*/
int Dynamic_KnapSack_sol(int **memoized, int index, int capacity, std::vector<int>& value, std::vector<int>& cap){
    if(memoized[index][capacity] != -1) return memoized[index][capacity];

    if(index < 0 || capacity == 0){
        return 0;
    }else if(capacity < cap[index]){
        memoized[index][capacity] = Dynamic_KnapSack_sol(memoized, index - 1, capacity, value, cap);
        return memoized[index][capacity];
    }else{
        memoized[index][capacity] = cap[index] + Dynamic_KnapSack_sol(memoized, index - 1, capacity - cap[index], value, cap);
        memoized[index][capacity] = std::max(Dynamic_KnapSack_sol(memoized, index - 1, capacity, value, cap), cap[index] + Dynamic_KnapSack_sol(memoized, index - 1, capacity - cap[index], value, cap));
        return memoized[index][capacity];
    }
}

int KnapSack_memoized(int index, int capacity, std::vector<int>& value, std::vector<int>& cap){
    // double pointer to declare the
    // table dynamically
    int** memoized;
    memoized = new int*[index];
    for(int i = 0; i < index; ++i){
        memoized[i] = new int[capacity+1];
    }

    std::fill(&memoized[0][0], &memoized[0][0] + sizeof(memoized), -1);
    Dynamic_KnapSack_sol(memoized, index, capacity, value, cap);
}

