#include <iostream>
#include <vector>

template <typename type_t>
std::vector<type_t> counting_sort(std::vector<type_t> input, u_int32_t maxElem){
    std::vector freqAcc(maxElem + 1, 0);

    for(auto& elem : input){
        ++freqAcc[elem];
    }

    for(auto elem : freqAcc)
        std:: cout << elem << " ";
    std::cout << "\n";

    for(auto elem = 1; elem < freqAcc.size(); ++elem){
        freqAcc[elem] = freqAcc[elem] + freqAcc[elem - 1];
    }

    for(auto elem : freqAcc)
        std:: cout << elem << " ";
    std::cout << "\n";

    std::vector<type_t> result(input.size());

    for (int i = input.size() - 1; i >= 0 ; --i){
        result[freqAcc[input[i]] - 1] = input[i];
        --freqAcc[input[i]];
    }

    return result;
}

int main(){
    std::vector<int>nums {1,5,1,1,6,4};
    std::vector<int>res = counting_sort(nums, 6);

    for(auto elem : res)
        std:: cout << elem << " ";
    std::cout << "\n";
}