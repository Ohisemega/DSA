#include <iostream>
#include <string>
#include <array>
template<size_t N>
void print_str(const std::string& str, std::array<bool, N>& bool_arr){
    for(int i = 0; i < N; ++i){
        if(bool_arr[i]) std::cout << str[i];
    }
    std::cout << '\n';
}

template<size_t M>
void print_substrings(const std::string& m_str, std::array<bool, M>& bool_arr, int n) {
    if(n < 0){
        print_str<M>(m_str, bool_arr);
        return;
    }
    bool_arr[n] = false;
    print_substrings(m_str, bool_arr, n-1);
    bool_arr[n] = true;
    print_substrings(m_str, bool_arr, n-1);
}


void caller(const std::string& str){
    std::array<bool, 4>bool_arr;
    bool_arr.fill(true);
    print_substrings<4>(str, bool_arr, str.size()-1);
}

int main(){
    caller("1234");
}
