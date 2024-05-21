#include <iostream>
#include <vector>

int count = 0;

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
void QuickSort(std::vector<type_t>& vec, int start, int end ){
    ++::count;
    if(start < end){
        int pivot = Partition(vec, start, end);
        for(auto itr: vec)
            std::cout << itr << ' ';
        std::cout << "\n";
        QuickSort(vec, start, pivot-1);
        QuickSort(vec, pivot + 1, end);
    }
}

int main(){
    std::vector<int> vec{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    QuickSort(vec, 0, vec.size()-1);

    std::cout << "The array is: \n";
    for(auto itr: vec)
        std::cout << itr << ' ';
    std::cout << "\n";
    std::cout << "The calls to Quicksort are: " << count;
    
}