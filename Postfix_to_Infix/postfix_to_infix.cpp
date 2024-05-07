#include <string>
#include <vector>
#include <stack>
#include <iostream>

std::string postfixToInfix(std::string& postfixExp){
	int len = postfixExp.length();
	postfixExp.cbegin();
	// std::string output = "";
	std::stack<std::string> stk;
	std::string&& sum = "";
	for(int i = 0; i < len; ++i) {
		if(postfixExp[i] == '-' && isdigit(postfixExp[i+1])){
			++i;
			std::string negVal = std::string() + "(" + "-" + postfixExp[i] + ")";
			stk.push(negVal);
		}else if(std::isdigit(postfixExp[i])){
			stk.push(std::string() + postfixExp[i]);
		}else if(postfixExp[i] == '+' || postfixExp[i] == '-' || postfixExp[i] == '*' || postfixExp[i] == '/'){
			sum = stk.top();
			stk.pop();
			sum = std::string("(" + stk.top() + postfixExp[i] + sum + ")");
			stk.pop();
			stk.push(sum);
		}else if(postfixExp[i] == '$'){
			sum = stk.top();
			stk.pop();
			sum = std::string() + "$(" + stk.top() + ")";
			stk.push(sum);
		}
		std::cout << "The final value is: " << i << std::endl;
		std::cout << "The stack top is: " << stk.top() << std::endl;
	}
	return stk.top();
}

int main(){
	// std::string expr{"5 9 8 + 4 6 * * 7 + *"};
	std::string expr{"-2 5 9 8 + 4 6 * * 7 $ + * -"};
	std::cout << "The value is: " << postfixToInfix(expr) << std::endl;
}