#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

/** Partitions [beg - end) 
 *  Where items that satisfy
 *  fn(item) == true
 *  are places at the beginning
 *  half of the array!
 */
template<typename Q, typename Func>
constexpr int stl_partition(std::vector<Q>& vec, int beg, int end, Func fn) {
    while(true) {
        while(true) {
            if(beg == end) return beg;
            else if(fn(vec[beg])) ++beg;
            else break;
        }
        --end;
        while(true) {
            if(beg == end) return beg;
            else if(!fn(vec[end])) --end;
            else break;
        }
        std::swap(vec[beg], vec[end]);
        ++beg;
    }
}

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
    if(start < end){
        int pivot = Partition(vec, start, end);
        QuickSort(vec, start, pivot-1);
        QuickSort(vec, pivot + 1, end);
    }
}

int main(){
    std::vector<int> vec{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    QuickSort(vec, 0, vec.size()-1);
    std::vector<int> test_vec = {20, -50, 14, 66, 37, 11, -19, 8, -1, 5, 100};
    stl_partition(test_vec, 0, test_vec.size(), [](auto a){ return a < 30; });
    std::copy(test_vec.begin(), test_vec.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << "\nThe array is: \n";
    for(auto itr: vec)
        std::cout << itr << ' ';
    std::cout << "\n";   
}
