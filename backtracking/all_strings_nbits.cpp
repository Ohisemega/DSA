#include <string>
#include <iostream>


void generate_string(std::string& str, int n){
    if(n <= 0){
        std::cout << str << "\n";
    }else{
        str[n] = '1';
        generate_string(str, n-1);
        str[n] = '0';
        generate_string(str, n-1);
    }
    
}

int main(){
    std::string str  = "0000000";
    generate_string(str, str.length()-1);
}