#include "heap.hpp"

int main(){

    std::vector<char> newVec{'c', 'h', 'a', 'r', 'i', 'n', 'd', 'o', 'n'};
    Heap<char> myCharHeap{std::move(newVec), HeapType::MAX_HEAP, PriorityQueue::NON_PRIORITY_QUEUE};

    myCharHeap.printHeap();
    myCharHeap.MaxHeapSort();
    myCharHeap.printHeap();
}