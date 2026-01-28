#include <string>
#include <iostream>

bool is_pal_rec(const std::string& str, int cnt){
    if(cnt >= (str.length()-1) >> 1) return true;

    if(str[cnt] != str[str.length()-1-cnt]) return false;
    return is_pal_rec(str, cnt+1);
}

int main(){
        std::cout << std::boolalpha << "The string is a Palindrom? " << is_pal_rec("HELLO ILLEH", 0) << '\n';    
}

