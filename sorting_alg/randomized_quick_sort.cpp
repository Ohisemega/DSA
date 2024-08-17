#include <iostream>
#include <vector>
#include <random>

template <typename type_t>
int Partition(std::vector<type_t>& vec, int beg, int end){
    type_t piv = vec[end];
    int i = beg - 1;
    for(int j = beg; j < end; ++j){
        if(vec[j] < piv){
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[end], vec[i+1]);
    
    return i+1;
}

template <typename type_t>
int randomized_partition(std::vector<type_t>& vec, int beg, int end){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(beg, end);

    std::swap(vec[end], vec[dist(rng)]);
    return Partition(vec, beg, end);
}

template <typename type_t>
void Randomized_QuickSort(std::vector<type_t>& vec, int start, int end ){
    if(start < end){
        int pivot = randomized_partition(vec, start, end);
        Randomized_QuickSort(vec, start, pivot-1);
        Randomized_QuickSort(vec, pivot + 1, end);
    }
}

int main(){
    std::vector<int> vec{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    Randomized_QuickSort(vec, 0, vec.size()-1);

    std::cout << "The array is: \n";
    for(auto itr: vec)
        std::cout << itr << ' ';
    std::cout << "\n";   
}