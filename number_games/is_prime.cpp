#include <iostream>

bool is_prime(int n){
    for(int i = 2; i*i <= n; ++i){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}


int main(){
    std::cout << std::boolalpha << "42 is a Prime: " << is_prime(42) << '\n';
    std::cout << std::boolalpha << "37 is a Prime: " << is_prime(37) << '\n';
}
