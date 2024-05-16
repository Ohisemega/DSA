#ifndef HEAP_CLASS
#define HEAP_CLASS
#include <cstddef>
#include <cstdint>
#include <vector>
#include <variant>
enum class HeapType{
    MAX_HEAP,
    MIN_HEAP,
};

enum class PriorityQueue{
    PRIORITY_QUEUE,
    NON_PRIORITY_QUEUE,
};
template <typename type_t>
class Heap{
    private:
        #define SUB_TREE_SIZE 3
        std::vector<type_t> array;
        int64_t heapSize;
        HeapType type;
        PriorityQueue qType;

        std::tuple<type_t, int64_t> findMaxIndex(int64_t parentIndx)const;
        std::tuple<type_t, int64_t> findMinIndex(int64_t parentIndx)const;

    protected:
    // helper functions
        std::pair<int64_t, bool> Parent(int64_t i) const;
        std::pair<int64_t, bool> LeftChild(int64_t i) const;
        std::pair<int64_t, bool> RightChild(int64_t i) const;
        void MaxHeapify(int64_t i);
        void MinHeapify(int64_t i);
        int64_t getHeapSize()const;
        int64_t getArraySize()const;
        HeapType getHeapType()const;
        auto getElement(int64_t)const;
        void BuildHeap();
        void InsertHeap(type_t insetElement);
        bool HeapIncreaseKey(int indx, int key);
        bool HeapDecreaseKey(int indx, int key);

    public:
        explicit Heap(std::vector<type_t>&&, HeapType type, PriorityQueue qtype);
        Heap(Heap<type_t>&) = delete;
        Heap<type_t>& operator=(const Heap<type_t>&) = delete;
        Heap(Heap<type_t>&&); // move constructor
        Heap<type_t>& operator=(const Heap<type_t>&&);
        virtual ~Heap();
        void configureHeapType(HeapType type);
        void MaxHeapSort();
        void MinHeapSort();
        void HeapDeleteElement(int64_t i);
};

template <typename data_t>
Heap<data_t>::Heap(std::vector<data_t>&& objArr, HeapType type, PriorityQueue qType){
    this->heapSize = objArr.size();
    this->qType = qType;
    this->array = std::move(objArr);
    this->type = type;
    this->BuildHeap();
}

template <typename data_t>
Heap<data_t>::Heap(Heap<data_t>&& mvObj){ // move constructor
    this->type = mvObj.type;
    this->heapSize = mvObj.heapSize;
    this->array = std::move(mvObj.array);
}

template <typename data_t>
Heap<data_t>& Heap<data_t>::operator=(const Heap<data_t>&& mvObj){
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
int64_t Heap<data_t>::getHeapSize()const{
    return this->heapSize;
}

template <typename data_t>
int64_t Heap<data_t>::getArraySize()const{
    return this->array.capacity();
}

template <typename data_t>
HeapType Heap<data_t>::getHeapType()const{
    return this->type;
}

template <typename data_t>
void Heap<data_t>::configureHeapType(HeapType type){
    if(this->type == type) return;
    this->type = type;
    this->BuildHeap();;
}

template <typename data_t>
auto Heap<data_t>::getElement(int64_t indx)const{
    if(indx < this->heapSize){
        return std::make_pair(array.at(indx-1), true);
    }
    static_assert(std::is_default_constructible<data_t>::value, "Class Heap data specialization is NOT default constructible!");
    data_t data;
    return std::make_pair(data, false);
}

template <typename type_t>
std::tuple<type_t, int64_t> Heap<type_t>::findMaxIndex(int64_t parentIndx)const{
    if(parentIndx > heapSize/2) return {array[parentIndx-1], parentIndx};
    
    size_t indxArr[SUB_TREE_SIZE] = {parentIndx, LeftChild(parentIndx).first, RightChild(parentIndx).first};
    type_t values[SUB_TREE_SIZE] = {array[parentIndx-1], array[indxArr[1]-1], array[indxArr[2]-1]};
    type_t maxKey;
    size_t i, max_i = parentIndx;
    if(this->qType == PriorityQueue::NON_PRIORITY_QUEUE){
        maxKey = array[parentIndx-1];
        for(i = 1; i < SUB_TREE_SIZE; ++i){
            if(values[i] > maxKey){
                maxKey = values[i];
                max_i = i;
            }
        }
    }else{
        maxKey = array[parentIndx-1].key;
        for(i = 1; i < SUB_TREE_SIZE; ++i){
            if(values[i].key > maxKey){
                maxKey = values[i].key;
                max_i = i;
            }
        }
    }
    return {maxKey, max_i};
}

template <typename type_t>
std::tuple<type_t, int64_t> Heap<type_t>::findMinIndex(int64_t parentIndx)const{
    if(parentIndx > heapSize/2) return {array[parentIndx-1], parentIndx};
    size_t indxArr[SUB_TREE_SIZE] = {parentIndx, LeftChild(parentIndx).first, RightChild(parentIndx).first};
    type_t values[SUB_TREE_SIZE] = {array[parentIndx-1], array[indxArr[1]-1], array[indxArr[2]-1]};
    type_t minKey;
    size_t i, min_i = parentIndx;

    if(this->qType == PriorityQueue::NON_PRIORITY_QUEUE){
        minKey = array[parentIndx-1];
        for(i = 1; i < SUB_TREE_SIZE; ++i){
            if(values[i] < minKey){
                minKey = values[i];
                min_i = i;
            }
        }
    }else{
        minKey = array[parentIndx-1].key;
        for(i = 1; i < SUB_TREE_SIZE; ++i){
            if(values[i].key < minKey){
                minKey = values[i].key;
                min_i = i;
            }
        }
    }
    return {minKey, min_i};
}

template <typename data_t>
std::pair<int64_t, bool> Heap<data_t>::Parent(int64_t i) const{
    if((i >= 2) && (i <= this->heapSize)){
        return std::make_pair(i/2, true);
    }
    return std::make_pair(1, false); // return the root of the heap
}

template <typename data_t>
std::pair<int64_t, bool> Heap<data_t>::LeftChild(int64_t i) const{
    if((i > 0) && (i < ((this->heapSize/2) + 1))){
        return std::make_pair(2*i, true);     
    }
    return std::make_pair(i, false);
}

template <typename data_t>
std::pair<int64_t, bool> Heap<data_t>::RightChild(int64_t i) const{
    if((i >= 1) && (i < ((this->heapSize/2) + 1))){
        return std::make_pair((2*i) + 1, true);     
    }
    return std::make_pair(i, false);
}

template <typename data_t>
void Heap<data_t>::MaxHeapify(int64_t i){
    // assumes that the sub-trees at the left and right child nodes are 
    // max-heaps or hold the max-heap property. Now it must verify that 
    // array[i] holds that same property with respect to it's left and right children, but 
    // that check may invalidate one sub-tree, hence we recursively call it.
    if(i > 0 && i <= this->heapSize/2){
        auto maxElem = findMaxIndex(i);
        if(std::get<int64_t>(maxElem) != i){
            std::swap(std::get<data_t>(maxElem), array[i-1]);
            MaxHeapify(std::get<int64_t>(maxElem));
        }
    }
}

template <typename data_t>
void Heap<data_t>::MinHeapify(int64_t i){
    // assumes that the sub-trees at the left and right child nodes are 
    // min-heaps or hold the min-heap property. Now it must verify that 
    // array[i-1] holds that same property with respect to it's left and right children, but 
    // that check may invalidate one sub-tree, hence we recursively call it.
    if(i > 0 && i <= this->heapSize/2){
        auto minElem = findMinIndex(i);
        if(std::get<int64_t>(minElem) != i){
            std::swap(std::get<data_t>(minElem), array[i-1]);
            MinHeapify(std::get<int64_t>(minElem));
        }
    }
}

template <typename data_t>
void Heap<data_t>::BuildHeap(){
    if(this->type == HeapType::MAX_HEAP){
        for (size_t i = heapSize/2; i > 0; --i){
            MaxHeapify(i);
        }
    }else{
        for (size_t i = heapSize/2; i > 0; --i){
            MinHeapify(i);
        }
    }
}

template <typename data_t>
void Heap<data_t>::InsertHeap(data_t insertElement){
    if(this->qType == PriorityQueue::PRIORITY_QUEUE){
        data_t pObj;
        pObj.data = insertElement.data;
        array.push_back(pObj);
        ++this->heapSize;
        this->HeapIncreaseKey(this->heapSize, insertElement.key);
    }else{
        array.push_back(insertElement);
        ++this->heapSize;
        this-BuildHeap();
    }
    
}

// heap-sort is about sorting the internal array, not the heap itself
template<typename data_t>
void Heap<data_t>::MaxHeapSort(){
    this->BuildHeap();
    for (;this->heapSize > 1; --this->heapSize){
        std::swap(array[1], array[heapSize-1]);
        MaxHeapify(1); // keep the maximum at the root of the tree, preserve max-heap property
    }
}

// heap-sort is about sorting the internal array, not the heap itself
template<typename data_t>
void Heap<data_t>::MinHeapSort(){
    this->BuildHeap();
    for (;this->heapSize > 1; --this->heapSize){
        std::swap(array[1], array[heapSize-1]); 
        MinHeapify(1); // keep the minimum at the root of the tree, preserve min-heap property
    }
}

template<typename data_t>
void Heap<data_t>::HeapDeleteElement(int64_t i){
    if(i <= this->heapSize){
        array[i-1] = array[heapSize-1];
        --this->heapSize;
        this->type == HeapType::MAX_HEAP ? this->MaxHeapify(i) : this->MinHeapify(i);
    }
}

template <typename data_t>
bool Heap<data_t>::HeapIncreaseKey(int indx, int key){
    bool ret = false;
    if(this->qType == PriorityQueue::PRIORITY_QUEUE && this->type == HeapType::MAX_HEAP && indx > 1 && indx <= this->heapSize \
        && array[indx-1].key < key){
        array[indx-1].key = key;
        ret = true;
        while (indx > 1 && (array[this->Parent(indx)-1].key < this->array[indx-1].key)){
            std::swap(array[this->Parent(indx)-1], array[indx-1]);
            indx = this->Parent(indx);
        }
    }
    return ret;
}

template <typename data_t>
bool Heap<data_t>::HeapDecreaseKey(int indx, int key){
    bool ret = false;
    if(this->qType == PriorityQueue::PRIORITY_QUEUE && this->type == HeapType::MIN_HEAP && indx > 1 && indx <= this->heapSize \
        && array[indx-1].key > key){
        array[indx-1].key = key;
        ret = true;
        while (indx > 1 && (array[this->Parent(indx)-1].key > this->array[indx-1].key)){
            std::swap(array[this->Parent(indx)-1], array[indx-1]);
            indx = this->Parent(indx);
        }
    }
    return ret;
}

#endif
