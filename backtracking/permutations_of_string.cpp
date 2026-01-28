#include <string>
#include <iostream>

// print all permutations of a string 


void all_perm(std::string& str, int idx, int id){
    // std::cout << str << '\n';
    if(idx == str.size()){
        std::cout << str << '\n';
        return;
    }
    for(int i = idx; i < str.size(); ++i){
//        std::cout <<"**BS " << id << ' ' << str << '\n';
        std::swap(str[idx], str[i]);
        all_perm(str, idx+1, id+1);
        std::swap(str[idx], str[i]);
//        std::cout <<"**" << id << '[' << i << "] " << str << '\n';
    }
}

int main(){
    std::string s{"ABC"};
    all_perm(s, 0, 0);
}
