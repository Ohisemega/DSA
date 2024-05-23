#include "heap.hpp"

int main(){

    std::vector<char> newVec{'c', 'h', 'a', 'r', 'i', 'n', 'd', 'o', 'n'};
    Heap<char> myCharHeap{std::move(newVec), HeapType::MAX_HEAP};

    myCharHeap.printHeap();
    myCharHeap.MaxHeapSort();
    myCharHeap.printHeap();
}