#include <iostream>

long double fac_tail_rec(long double acc, uint32_t value){
    if(value < 2) return acc;
    return fac_tail_rec(acc*value, value - 1);
}

long double fac(uint32_t n){
    return fac_tail_rec(1, n);
}

int main(){
    std::cout << "The factorial of 89 is " << fac(1000) << std::endl;
    std::cout << "The Max value of uint64 is " << __LDBL_MAX__ << std::endl;
}

//  9223372036854775808
// 18446744073709551615