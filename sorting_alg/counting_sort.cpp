#include <iostream>
#include <vector>

template <typename type_t>
std::vector<type_t> counting_sort(std::vector<type_t> input, u_int32_t maxElem){
    std::vector freq(maxElem + 1, 0);
    std::vector freqAcc(maxElem + 1, 0);

    for(auto& elem : input){
        ++freq[elem];
    }

    freqAcc[0] = freq[0];
    for(auto elem = 0; elem < maxElem + 1; ++freq){
        freqAcc[elem] = freq[elem] + freqAcc[elem - 1];
    }

    std::vector<type_t> result(maxElem);

    for (int i = input.size() - 1; i >= 0 ; --i){
        result[freqAcc[input[i]] - 1] = input[i];
    }

    return result;
}

