#include <deque>
#include <string>
#include <cctype>
#include <iostream>
#include <type_traits>

// template <typename item>
auto isSequencePossible(const std::string& input_str, const std::string& output_str)-> std::decay<decltype(true)>::type{
    std::deque<char> container;
    bool isPossible = true;
    size_t output_len = output_str.length();
    size_t input_len  = input_str.length();
    size_t output_counter = 0, input_counter = 0;
    while (output_counter < output_len && isPossible)
    {
        if(!container.empty() && output_str[output_counter] == container.front()){
            container.pop_front();
            ++output_counter;
        }else if(!container.empty() && output_str[output_counter] == container.back()){
            container.pop_back();
            ++output_counter;
        }else if(output_str[output_counter] == input_str[input_counter]){
            ++output_counter;
            ++input_counter;
        }else if(output_counter < output_len && input_counter < input_len){
            if(islower(input_str[input_counter])){
                container.push_back(input_str[input_counter]);
            }else {
                container.push_front(input_str[input_counter]);
            }
            ++input_counter;
        }else{
            isPossible = false;
        }
    }
    return isPossible;
}


int main(int argc, char* argv[]){
    std::string in{"EasY"};
    std::string out {"asYE"};
    if(::isSequencePossible(in, out)){
        std::cout << "It is Possible!\n";
    }else{
        std::cout << "It is not Possible!\n";
    }
}
