#include <array>
#include <iostream>

template <std::size_t N>
void rev_arr_impl(std::array<int, N>& arr, int cnt) {
    if(cnt >= N-cnt-1) return;

    std::swap(arr[cnt], arr[N-cnt-1]);
    rev_arr_impl(arr, cnt+1);
}

template <std::size_t N>
void rev_arr(std::array<int, N>& arr){
    rev_arr_impl(arr, 0);
}


int main(){
    std::array<int, 5> arr{1, 2, 3, 4 ,5};
    rev_arr<5>(arr);
    for(int i = 0; i < 5; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}
