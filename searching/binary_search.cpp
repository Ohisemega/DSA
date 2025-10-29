#include <iostream>
#include <variant>
#include <string>
#include <vector>

template<typename Item>
std::pair<Item, bool> bsearch(std::vector<Item>& vec, Item key){
    size_t size = vec.size();
    size_t left = 0, right = size-1;
    for (size_t i = 0; left < right; ++i){
        size_t mid = (left+right)/2;
        if(vec[mid] > key){
            right = mid-1;
        }else if(vec[mid] < key){
            left = mid+1;
        }else{
            return {key, true};
        }
    }
    return {key, false};
}


int main(){
    std::vector<int> vect = {1, 2, 3, 4, 5, 7, 9, 11, 15, 15, 20, 21, 45, 89, 100, 1105, 106, 107};

    std::cout << std::boolalpha << "Presence of the number 0 is: " << bsearch(vect, 0).second << "\n";
    std::cout << std::boolalpha << "Presence of the number 15 is: " << bsearch(vect, 15).second << "\n";
}