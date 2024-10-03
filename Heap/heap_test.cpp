#include "heap.hpp"

int main(){
    Heap<char> myCharHeap{std::vector<char>{'c', 'h', 'a', 'r', 'i', 'n', 'd', 'o', 'n'}, HeapType::MAX_HEAP};
    std::cout << "The heap before insertion: ";
    myCharHeap.printHeap();
    std::cout << "Insertion time:\n ";
    myCharHeap.InsertHeap('q');
    std::cout << "The heap after insertion: ";
    myCharHeap.printHeap();
    myCharHeap.MaxHeapSort();
    myCharHeap.printHeap();
}