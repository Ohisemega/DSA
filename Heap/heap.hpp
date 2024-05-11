#ifndef HEAP_CLASS
#define HEAP_CLASS
#include <cstddef>
#include <vector>
#include <variant>
enum class HeapType{
    NOT_INIT,
    MAX_HEAP,
    MIN_HEAP,
};
template <typename type_t>
class Heap{
    private:
        #define SUB_TREE_SIZE 3
        std::vector<type_t> array;
        std::size_t heapSize;
        HeapType type;

        std::tuple<type_t, std::size_t> findMaxIndex(std::size_t parentIndx)const;
        std::tuple<type_t, std::size_t> findMinIndex(std::size_t parentIndx)const;

    protected:
    // helper functions
        std::pair<std::size_t, bool> Parent(std::size_t i) const;
        std::pair<std::size_t, bool> LeftChild(std::size_t i) const;
        std::pair<std::size_t, bool> RightChild(std::size_t i) const;
        void MaxHeapify(std::size_t i);
        void MinHeapify(std::size_t i);
        std::size_t getHeapSize()const;
        std::size_t getArraySize()const;
        HeapType getHeapType()const;
        // void resizeHeap(std::size_t increament);

    public:
        Heap(std::vector<type_t>&&);
        virtual ~Heap();
        bool BuildMaxHeap();
        bool BuildMinHeap();
        void MaxHeapSort();
        void MinHeapSort();
};

template <typename data_t>
Heap<data_t>::Heap(std::vector<data_t>&& objArr){
    this->heapSize = ;
    this->array(std::move(objArr));
}

template <typename data_t>
Heap<data_t>::~Heap(){

}

template <typename data_t>
std::size_t Heap<data_t>::getHeapSize()const{
    return this->heapSize;
}

template <typename data_t>
std::size_t Heap<data_t>::getArraySize()const{
    return this->array.capacity();
}

template <typename data_t>
HeapType Heap<data_t>::getHeapType()const{
    return this->type;
}

template <typename type_t>
std::tuple<type_t, std::size_t> Heap<type_t>::findMaxIndex(std::size_t parentIndx)const{
    if(parentIndx > heapSize/2) return {array[parentIndx-1], parentIndx};
    size_t indxArr[SUB_TREE_SIZE] = {parentIndx, LeftChild(parentIndx).first, RightChild(parentIndx).first};
    type_t values[SUB_TREE_SIZE] = {array[parentIndx-1], array[indxArr[1]-1], array[indxArr[2]-1]};
    type_t max = array[parentIndx-1];
    size_t i, max_i = parentIndx;
    for(i = 1; i < SUB_TREE_SIZE; ++i){
        if(values[i] > max){
            max = value[i];
            max_i = i;
        }
    }
    return {max, max_i};
}

template <typename type_t>
std::tuple<type_t, std::size_t> Heap<type_t>::findMinIndex(std::size_t parentIndx)const{
    if(parentIndx > heapSize/2) return {array[parentIndx-1], parentIndx};
    size_t indxArr[SUB_TREE_SIZE] = {parentIndx, LeftChild(parentIndx).first, RightChild(parentIndx).first};
    type_t values[SUB_TREE_SIZE] = {array[parentIndx-1], array[indxArr[1]-1], array[indxArr[2]-1]};
    type_t min = array[parentIndx-1];
    size_t i, min_i = parentIndx;
    for(i = 1; i < SUB_TREE_SIZE; ++i){
        if(values[i] < min){
            min = value[i];
            min_i = i;
        }
    }
    return {min, min_i};
}

template <typename data_t>
std::pair<std::size_t, bool> Heap<data_t>::Parent(std::size_t i) const{
    if((i >= 2) && (i/2 < this->heapSize)){
        return std::make_pair(i/2, true);
    }
    return std::make_pair(1, false); // return the root of the heap
}

template <typename data_t>
std::pair<std::size_t, bool> Heap<data_t>::LeftChild(std::size_t i) const{
    if((i >= 1) && (i < ((this->heapSize/2) + 1))){
        return std::make_pair(2*i, true);     
    }
    return std::make_pair(i, false);
}

template <typename data_t>
std::pair<std::size_t, bool> Heap<data_t>::RightChild(std::size_t i) const{
    if((i >= 1) && (i < ((this->heapSize/2) + 1))){
        return std::make_pair((2*i) + 1, true);     
    }
    return std::make_pair(i, false);
}

template <typename data_t>
void Heap<data_t>::MaxHeapify(std::size_t i){
    // assumes that the sub-trees at the left and right child nodes are 
    // max-heaps or hold the max-heap property. Now it must verify that 
    // array[i] holds that same property with respect to it's left and right children, but 
    // that check may invalidate one sub-tree, hence we recursively call it.
    if(i > 0 && i <= this->heapSize/2){
        auto maxElem = findMaxIndex(i);
        if(std::get<std::size_t>(maxElem) != i){
            std::swap(std::get<data_t>(maxElem), array[i-1]);
            MaxHeapify(std::get<std::size_t>(maxElem));
        }
    }
}

template <typename data_t>
void Heap<data_t>::MinHeapify(std::size_t i){
    // assumes that the sub-trees at the left and right child nodes are 
    // min-heaps or hold the min-heap property. Now it must verify that 
    // array[i] holds that same property with respect to it's left and right children, but 
    // that check may invalidate one sub-tree, hence we recursively call it.
    if(i > 0 && i <= this->heapSize/2){
        auto minElem = findMinIndex(i);
        if(std::get<std::size_t>(minElem) != i){
            std::swap(std::get<data_t>(minElem), array[i-1]);
            MinHeapify(std::get<std::size_t>(minElem));
        }
    }
}

template <typename data_t>
bool Heap<data_t>::BuildMaxHeap(){
    bool ret = this->type == HeapType::MAX_HEAP ? true : false;
    if (ret){
        for (size_t i = heapSize/2; i > 0; --i){
            MaxHeapify(i);
        }
    }
    return ret;
}

template <typename data_t>
bool Heap<data_t>::BuildMinHeap(){
    bool ret = this->type == HeapType::MIN_HEAP ? true : false;
    if (ret){
        for (size_t i = heapSize/2; i > 0; --i){
            MinHeapify(i);
        }
    }
    return ret;
}

// heap-sort is about sorting the internal array, not the heap itself
template<typename data_t>
void Heap<data_t>::MaxHeapSort(){
    BuildMaxHeap();
    for (this->heapSize > 1; --this->heapSize){
        std::swap(array[1], array[heapSize]);
        MaxHeapify(1); // keep the maximum at the root of the tree, preserve max-heap property
    }
}

// heap-sort is about sorting the internal array, not the heap itself
template<typename data_t>
void Heap<data_t>::MinHeapSort(){
    BuildMinHeap();
    for (this->heapSize > 1; --this->heapSize){
        std::swap(array[1], array[heapSize]); 
        MinHeapify(1); // keep the minimum at the root of the tree, preserve min-heap property
    }
}

#endif
