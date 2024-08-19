#include <iostream>

uint64_t fibonnacci(size_t n){
    uint64_t prev[2] = {0, 1};
    uint64_t result = 0;

    for(size_t i = 2; i <= n; ++i){
        result = prev[0] + prev[1];
        prev[0] = prev[1];
        prev[1] = result;
    }
    return result;
}