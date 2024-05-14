#include "random_queue.hpp"
#include <iostream>



int main(int argc, char* argv[]){
    rand_queue_template::RandomQueue<int64_t> randQueue{10};
    randQueue.enque(1);
    randQueue.printArray();
    randQueue.enque(2);
    randQueue.printArray();
    randQueue.enque(3);
    randQueue.printArray();
    randQueue.enque(4);
    randQueue.printArray();
    randQueue.enque(5);
    randQueue.printArray();
    randQueue.enque(6);
    randQueue.printArray();
    randQueue.enque(7);
    randQueue.printArray();
    randQueue.enque(8);
    randQueue.printArray();
    randQueue.enque(9);
    randQueue.printArray();
    randQueue.enque(10);
    randQueue.printArray();

    for(int i = 20; i > 0; --i){
        std::pair<int32_t, bool> randItem;
        randItem = randQueue.sample();
        std::cout << "The released item is: " << randItem.first << "\n";
        randQueue.printArray();
    }
}