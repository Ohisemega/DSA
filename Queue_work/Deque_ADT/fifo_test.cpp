#include "FIFO_queue_adt.hpp"
#include "deque.hpp"
#include <iostream>

int main(){
    deque_template::Deque<int> myDeque{10};
    myDeque.printArray();
    std::pair<int, bool> retPair;
    myDeque.push_back(1);
    myDeque.printArray();
    myDeque.push_back(2);
    myDeque.printArray();
    myDeque.push_back(3);
    myDeque.printArray();
    myDeque.push_back(4);
    myDeque.printArray();
    myDeque.push_back(5);
    myDeque.printArray();
    myDeque.push_back(6);
    myDeque.printArray();
    myDeque.push_back(7);
    myDeque.printArray();
    myDeque.push_back(8);
    myDeque.printArray();
    myDeque.push_back(9);
    myDeque.printArray();
    myDeque.push_back(10);
    myDeque.printArray();
    myDeque.push_back(11);
    myDeque.printArray();

    if((retPair = myDeque.at(1)).second)
    {
        std::cout << "At is: " << retPair.first << "\n";
    }

    while ((retPair = myDeque.pop_back()).second)
    // while(!myDeque.isEmpty())
    {
        // std::cout << "Not empty!\n";
        // retPair = myDeque.pop_back();
        std::cout << retPair.first << "\n";
        // std::cout << myDeque.pop_back().first << "\n";
    }

    myDeque.push_back(10);
    myDeque.printArray();
    int retVal = myDeque.pop_front().first;
    std::cout << "our ret val is: " << retVal << "\n";
    retVal = myDeque.pop_front().first;
    std::cout << "our ret val is: " << retVal << "\n";
    myDeque.printArray();
    // std::cout << "\n\n";

    // QueueCirList<int> myQueue;
    // myQueue.putItem(1);
    // myQueue.putItem(2);
    // myQueue.putItem(3);
    // myQueue.putItem(1);
    // myQueue.putItem(4);
    // myQueue.putItem(8);

    // while(!myQueue.isEmpty()){
    //     std::cout << myQueue.get().first << "\n";
    // }
}