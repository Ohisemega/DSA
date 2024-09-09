#include <iostream>
#include <vector>

int maxSubArray(std::vector<int>& Arr){
    int size = Arr.size();
    int local_max = 0;
    int global_max = INT32_MIN;
    int start = 0;
    int end = 0;
    for (size_t i = 0; i < size; ++i){
        local_max =  std::max(Arr[i], Arr[i] + local_max);
        if(local_max > global_max){
            global_max = local_max;
        }
    }
    
    return global_max;
}

int main(){
    std::vector<int> vec{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "The max sub-array val is: " << maxSubArray(vec) << "\n";
}