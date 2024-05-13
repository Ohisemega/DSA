#include "stack_array.hpp"

int main(){
    STACK<int> myIntStack{STACK<int>{20}};
    STACK<int> testCopy{5};
    myIntStack.push(2);
    myIntStack.printIntArray();
    myIntStack.push(4);
    myIntStack.printIntArray();
    myIntStack.push(6);
    myIntStack.printIntArray();
    myIntStack.push(8);
    myIntStack.printIntArray();
    myIntStack.push(10);
    myIntStack.printIntArray();
    myIntStack.push(1);
    myIntStack.printIntArray();
    myIntStack.push(3);
    myIntStack.printIntArray();
    myIntStack.push(5);
    myIntStack.printIntArray();
    myIntStack.pop();
    myIntStack.printIntArray();
    myIntStack.push(2);
    myIntStack.printIntArray();

    testCopy = myIntStack;
    testCopy = std::move(myIntStack);    
    testCopy.printIntArray();
}