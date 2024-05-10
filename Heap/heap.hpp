#ifndef HEAP_CLASS
#define HEAP_CLASS
#include 
template <typename type_t>
class Heap{
    private:
        type_t* array;
        std::size_t N; // array Size;

    protected:
    // helper functions
        std::size_t Parent(std::size_t i) const;
        std::size_t LeftChild(std::size_t i) const;
        std::size_t RightChild(std::size_t i) const;
        void MaxHeapify(std::size_t i);
        void MinHeapify(std::size_t i);

    public:
        heap(int = 10);
        virtual ~heap();
        BuildMaxHeap();
        BuildMinHeap();
        MaxHeapSort();
        MinHeapSort();
};


#endif