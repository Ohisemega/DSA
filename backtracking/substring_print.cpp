#include <iostream>
#include <string>

void print_t(const std::string& str) {
    for(int i = 0; i < str.size(); ++i){
        for(int k = i+1; k < str.size(); k += 2){
            std::cout << str.substr(i, k-i+1);
            std::cout << '\n';
        }
    }
}

int main(){
    print_t("HelloWorld");
}
