#include <stack>
#include <string>
#include <iostream>
// Given two sequences, give an algorithm for determining whether or not
// asterisks can be added to make the first produce the second, when interpreted
// as a sequence of stack operations 

bool stack_sequence(const std::string& org_str, const std::string& output_str){
    std::stack<char> stck;
    int j = 0;
    bool boolean = true;
    for(int i = 0; i < org_str.length(); ++i){
        if(output_str[j] == org_str[i]){
            //pass
            ++j;
        }else{
            stck.push(org_str[i]);
        }
    }
    while (!stck.empty())
    {
        if(stck.top() == output_str[j]){
            stck.pop();
            ++j;
        }else{
            boolean = false;
            break;
        }
    }
    return boolean;
}

int main(){
    if(stack_sequence(std::string("EASY"), std::string("ASEY"))){
        std::cout << "It is Possible\n";
    }else{
        std::cout << "It is not Possible\n";
    }
}