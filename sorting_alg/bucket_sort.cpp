#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include "../list_problems/linked_list.hpp"


template<typename type_t>
void bucket_sort(std::vector<type_t>& input, int n){
    std::vector<std::list<type_t>> buckets(n+1);

    
    for(type_t elem : input){
        buckets[n*elem].insert(buckets[n*elem].begin(), elem);
    }

     
    for (std::list<type_t> elem : buckets){
        elem.sort();
    }

    for (size_t i = 0, j = 0; i < buckets.size(), j < input.size(); i++){
        
        for(auto elem : buckets[i]){
            input[j] = elem;
            ++j;
        }
    }
}

// Driver program to test above function
int main() {
    std::vector<float> arr = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    bucket_sort(arr, arr.size());

    std::cout << "Sorted array is \n";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    return 0;
}