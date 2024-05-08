#include <iostream>
#include "../Queue_work/Deque_ADT/FIFO_queue_adt.hpp"

// detect cycle in a linked list


int main(){
    Circular_List::QueueCirList<int32_t> roundList;
    roundList.putItem(2);
    roundList.putItem(4);
    roundList.putItem(5);
    roundList.putItem(3);
    roundList.putItem(21);
    roundList.putItem(31);
    roundList.putItem(83);
    roundList.putItem(12);
    roundList.putItem(7);
    roundList.putItem(71);

    roundList.detect_circular_list();
}