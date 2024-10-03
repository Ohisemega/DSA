#ifndef HEAP_CLASS
#define HEAP_CLASS
#include <cstddef>
#include <cstdint>
#include <vector>
#include <variant>
#include <iostream>
enum class HeapType{
    MAX_HEAP,
    MIN_HEAP,
};

template <typename type_t>
class Heap{
    private:
        #define SUB_TREE_SIZE 3
        std::vector<type_t> array;
        int64_t heapSize;
        HeapType type;

        std::pair<type_t, int64_t> findMaxIndex(int64_t parentIndx)const;
        std::pair<type_t, int64_t> findMinIndex(int64_t parentIndx)const;

    protected:
    // helper functions
        inline std::pair<int64_t, bool> Parent(int64_t i) const;
        inline std::pair<int64_t, bool> LeftChild(int64_t i) const;
        inline std::pair<int64_t, bool> RightChild(int64_t i) const;
        void MaxHeapify(int64_t i) noexcept;
        void MinHeapify(int64_t i) noexcept;
        constexpr int64_t getHeapSize()const noexcept;
        constexpr int64_t getArraySize()const noexcept;
        constexpr HeapType getHeapType()const noexcept;
        std::pair<type_t, bool> getElement(int64_t)const;
        std::pair<type_t&, bool> getElement(int64_t);
        void BuildHeap();
        void HeapIncreaseKey(int indx)noexcept;
        void HeapDecreaseKey(int indx)noexcept;

    public:
        Heap()=delete;
        explicit Heap(std::vector<type_t>&&, HeapType = HeapType::MAX_HEAP);
        Heap(std::initializer_list<type_t>, HeapType = HeapType::MAX_HEAP);
        Heap(const Heap<type_t>&) =delete; // conversion operator
        Heap<type_t>& operator=(const Heap<type_t>&) =delete;  // copy assignment operator deleted
        Heap(Heap<type_t>&&)noexcept; // move constructor
        Heap<type_t>& operator=(const Heap<type_t>&&) noexcept; // move assignment operator
        virtual ~Heap();
        void configureHeapType(HeapType type);
        void MaxHeapSort();
        void MinHeapSort();
        void InsertHeap(type_t insetElement);
        void HeapDeleteElement(int64_t i);
        void printHeap() const;
};

template <typename data_t>
void Heap<data_t>::printHeap()const{
    for (size_t i = 0; i < array.size(); ++i){
        std::cout << this->array[i] << " ";
    }
    std::cout << std::endl;
}

template <typename data_t>
Heap<data_t>::Heap(std::vector<data_t>&& objArr, HeapType type){
    this->heapSize = objArr.size();
    this->array = std::move(objArr);
    this->type = type;
    // this->printHeap();
    this->BuildHeap();
}

// initializer list constructor
template <typename data_t>
Heap<data_t>::Heap(std::initializer_list<data_t> list, HeapType type) : array(list){
    this->heapSize = list._M_len;
    this->type = type;
    // this->printHeap();
    this->BuildHeap();
}

template <typename data_t>
Heap<data_t>::Heap(Heap<data_t>&& mvObj) noexcept{ // move constructor
    this->type = mvObj.type;
    this->heapSize = mvObj.heapSize;
    this->array = std::move(mvObj.array);
}

template <typename data_t>
Heap<data_t>& Heap<data_t>::operator=(const Heap<data_t>&& mvObj) noexcept{
    this->type = mvObj.type;
    this->heapSize = mvObj.heapSize;
    this->array = std::move(mvObj.array);
    mvObj.heapSize = -1;
}

template <typename data_t>
Heap<data_t>::~Heap(){
    this->heapSize = -1;
}

template <typename data_t>
constexpr int64_t Heap<data_t>::getHeapSize()const noexcept{
    return this->heapSize;
}

template <typename data_t>
constexpr int64_t Heap<data_t>::getArraySize()const noexcept{
    return this->array.capacity();
}

template <typename data_t>
constexpr HeapType Heap<data_t>::getHeapType()const noexcept{
    return this->type;
}

template <typename data_t>
void Heap<data_t>::configureHeapType(HeapType type){
    if(this->type == type) return;
    this->type = type;
    this->BuildHeap();
}

template <typename data_t>
std::pair<data_t, bool> Heap<data_t>::getElement(int64_t indx)const{
    if(indx < this->heapSize){
        return std::make_pair(array[indx-1], true);
    }
    static_assert(std::is_default_constructible<data_t>::value, "Class Heap data specialization is NOT default constructible!");
    data_t data;
    return std::make_pair(data, false);
}

template <typename data_t>
std::pair<data_t&, bool> Heap<data_t>::getElement(int64_t indx){
    if(indx < 1 || indx >= this->heapSize) throw std::out_of_range{"Subscript out of range!"};
    return array[indx];
}


template <typename type_t>
std::pair<type_t, int64_t> Heap<type_t>::findMaxIndex(int64_t parentIndx)const{
    if(parentIndx > (heapSize >> 1)) return {array[parentIndx-1], parentIndx};
    
    int64_t indxArr[SUB_TREE_SIZE] = {parentIndx, LeftChild(parentIndx).first, RightChild(parentIndx).first};
    type_t values[SUB_TREE_SIZE] = {array[parentIndx-1], array[indxArr[1]-1], array[indxArr[2]-1]};
    type_t maxKey;
    size_t i;
    int64_t max_i = parentIndx;

    maxKey = array[parentIndx-1];
    // maxKey = 0;
    for(i = 1; i < SUB_TREE_SIZE; ++i){
        if(values[i] > maxKey){
            maxKey = values[i];
            max_i = indxArr[i];
        }
    }
    return {maxKey, max_i};
}

template <typename type_t>
std::pair<type_t, int64_t> Heap<type_t>::findMinIndex(int64_t parentIndx)const{
    if(parentIndx > heapSize >> 1) return {array[parentIndx-1], parentIndx};
    int64_t indxArr[SUB_TREE_SIZE] = {parentIndx, LeftChild(parentIndx).first, RightChild(parentIndx).first};
    type_t values[SUB_TREE_SIZE] = {array[parentIndx-1], array[indxArr[1]-1], array[indxArr[2]-1]};
    type_t minKey;
    size_t i; 
    int64_t min_i = parentIndx;

    minKey = array[parentIndx-1];
    for(i = 1; i < SUB_TREE_SIZE; ++i){
        if(values[i] < minKey){
            minKey = values[i];
            min_i = indxArr[i];
        }
    }
    return {minKey, min_i};
}

template <typename data_t>
std::pair<int64_t, bool> Heap<data_t>::Parent(int64_t i) const{
    if((i >= 2) && (i <= this->heapSize)){
        return {i >> 1, true};
    }
    return {1, false}; // return the root of the heap
}

template <typename data_t>
std::pair<int64_t, bool> Heap<data_t>::LeftChild(int64_t i) const{
    if((i > 0) && (i < ((this->heapSize >> 1) + 1)) && (2*i) <= this->heapSize){
        return std::make_pair(2*i, true);     
    }
    return {i, false};
}

template <typename data_t>
std::pair<int64_t, bool> Heap<data_t>::RightChild(int64_t i) const{
    if((i >= 1) && (i < ((this->heapSize >> 1) + 1)) && ((2*i)+1) <= this->heapSize){
        return std::make_pair((2*i) + 1, true);     
    }
    return {i, false};
}

template <typename data_t>
void Heap<data_t>::MaxHeapify(int64_t i) noexcept{
    // assumes that the sub-trees at the left and right child nodes are 
    // max-heaps or hold the max-heap property. Now it must verify that 
    // array[i] holds that same property with respect to it's left and right children, but 
    // that check may invalidate one sub-tree, hence we recursively call it.
    if(i > 0 && i <= this->heapSize >> 1){
        std::pair<data_t, int64_t> maxElem = findMaxIndex(i);
        if(maxElem.second != i){
            std::swap(array[maxElem.second-1], array[i-1]);
            MaxHeapify(maxElem.second);
        }
    }
}

template <typename data_t>
void Heap<data_t>::MinHeapify(int64_t i) noexcept{
    // assumes that the sub-trees at the left and right child nodes are 
    // min-heaps or hold the min-heap property. Now it must verify that 
    // array[i-1] holds that same property with respect to it's left and right children, but 
    // that check may invalidate one sub-tree, hence we recursively call it.
    if(i > 0 && i <= (this->heapSize >> 1)){
        std::pair<data_t, int64_t> minElem = findMinIndex(i);
        if(minElem.second != i){
            std::swap(array[minElem.second-1], array[i-1]);
            MinHeapify(std::get<int64_t>(minElem));
        }
    }
}

template <typename data_t>
void Heap<data_t>::BuildHeap(){
    if(this->type == HeapType::MAX_HEAP){
        for (size_t i = this->heapSize >> 1; i > 0; --i){
            MaxHeapify(i);
        }
    }else{
        for (size_t i = heapSize >> 1; i > 0; --i){
            MinHeapify(i);
        }
    }
}

template <typename data_t>
void Heap<data_t>::InsertHeap(data_t insertElement){
    array.push_back(insertElement);
    ++this->heapSize;
    this->BuildHeap();
    // this->MaxHeapify(this->heapSize >> 1);
    // int64_t i = this->heapSize;
    // while(i > 0 && this->array[(i-1)/2] < this->array[i-1]){
    //     std::swap(this->array[(i-1)/2], this->array[i-1]);
    //     i >>= 1;
    // }
}

// heap-sort is about sorting the internal array, not the heap itself
template<typename data_t>
void Heap<data_t>::MaxHeapSort(){
    for (;this->heapSize > 1;){
        std::swap(array[0], array[heapSize-1]);
        this->printHeap();
        --this->heapSize;
        MaxHeapify(1); // keep the maximum at the root of the tree, preserve max-heap property for 1 to heapsize
        this->printHeap();
    }
}

// heap-sort is about sorting the internal array, not the heap itself
template<typename data_t>
void Heap<data_t>::MinHeapSort(){
    for (;this->heapSize > 1; --this->heapSize){
        std::swap(array[0], array[heapSize-1]); 
        MinHeapify(1); // keep the minimum at the root of the tree, preserve min-heap property
    }
}

template<typename data_t>
void Heap<data_t>::HeapDeleteElement(int64_t i){
    if(i > 0 && i <= this->heapSize){
        array[i-1] = array[heapSize-1];
        --this->heapSize;
        this->type == HeapType::MAX_HEAP ? this->MaxHeapify(i) : this->MinHeapify(i);
    }
}

template <typename data_t>
void Heap<data_t>::HeapIncreaseKey(int indx)noexcept{
    if(this->type == HeapType::MAX_HEAP && indx > 1 && indx <= this->heapSize){
        while (indx > 1 && (array[this->Parent(indx)-1] < this->array[indx-1])){
            std::swap(array[this->Parent(indx)-1], array[indx-1]);
            indx = this->Parent(indx);
        }
    }
}

template <typename data_t>
void Heap<data_t>::HeapDecreaseKey(int indx)noexcept{
    if(this->type == HeapType::MIN_HEAP && indx > 1 && indx <= this->heapSize){
        while (indx > 1 && (array[this->Parent(indx)-1] > this->array[indx-1])){
            std::swap(array[this->Parent(indx)-1], array[indx-1]);
            indx = this->Parent(indx);
        }
    }
}

#endif
