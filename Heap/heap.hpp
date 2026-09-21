#ifndef HEAP_CLASS
#define HEAP_CLASS
#include <cstddef>
#include <cstdint>
#include <vector>
#include <optional>
// #include <variant>
#include <iostream>
enum class HeapType {
    MAX_HEAP,
    MIN_HEAP,
};

/*The Policy of our heap implementation is that:
    ONLY when we access the array do we utilize the 
    index - 1 property because we transform an example array
    given as: 0, 1, 2, 3 --> 1, 2, 3, 4*/

template <typename type_t>
class Heap {
    private:
        #define SUB_TREE_SIZE 3
        std::vector<type_t> array;
        int64_t heapSize;
        HeapType type;

        int64_t findMaxIndex(int64_t parentIndx) const noexcept;
        int64_t findMinIndex(int64_t parentIndx) const noexcept;

    protected:
    // helper functions
        inline std::optional<int64_t> Parent(int64_t i) const noexcept;
        inline std::optional<int64_t> LeftChild(int64_t i) const noexcept;
        inline std::optional<int64_t> RightChild(int64_t i) const noexcept;
        void MaxHeapify(int64_t i) noexcept;
        void MinHeapify(int64_t i) noexcept;
        constexpr int64_t getHeapSize()const noexcept;
        constexpr int64_t getArraySize()const noexcept;
        constexpr HeapType getHeapType()const noexcept;
        std::optional<type_t> getElement(int64_t) const noexcept;
        std::optional<type_t&> getElement(int64_t) noexcept;
        void BuildHeap() noexcept;
        bool changeElement(type_t data, type_t new_data) const noexcept;

    public:
        Heap()=delete;
        explicit Heap(std::vector<type_t>&&, HeapType = HeapType::MAX_HEAP);
        Heap(std::initializer_list<type_t>, HeapType = HeapType::MAX_HEAP);
        Heap(const Heap<type_t>&) =delete; // conversion operator
        Heap<type_t>& operator=(const Heap<type_t>&) =delete;  // copy assignment operator deleted
        Heap(Heap<type_t>&&)noexcept; // move constructor
        Heap<type_t>& operator=(Heap<type_t>&&) noexcept; // move assignment operator
        virtual ~Heap();
        void configureHeapType(HeapType type) noexcept;
        void MaxHeapSort() noexcept;
        void MinHeapSort() noexcept;
        void InsertHeap(type_t insetElement);
        void HeapDeleteElement(int64_t i) noexcept;
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
Heap<data_t>::Heap(Heap<data_t>&& mvObj) noexcept { // move constructor
    this->type = mvObj.type;
    this->heapSize = mvObj.heapSize;
    this->array = std::move(mvObj.array);
}

template <typename data_t>
Heap<data_t>& Heap<data_t>::operator=(Heap<data_t>&& mvObj) noexcept {
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
void Heap<data_t>::configureHeapType(HeapType type) noexcept {
    if(this->type == type) return;
    this->type = type;
    this->BuildHeap();
}

template <typename data_t>
std::optional<data_t> Heap<data_t>::getElement(int64_t idx) const noexcept {
    if((idx > 0) & (idx <= this->heapSize)) {
        return array[idx-1];
    }
    return {};
}

template <typename data_t>
std::optional<data_t&> Heap<data_t>::getElement(int64_t idx) noexcept {
    if((idx > 0) & (idx <= this->heapSize)) return array[idx-1];
    return {};
}


template <typename type_t>
int64_t Heap<type_t>::findMaxIndex(int64_t parentIndx) const noexcept {
    if(parentIndx > (heapSize >> 1)) return parentIndx;
    
    int64_t indxArr[SUB_TREE_SIZE] = {parentIndx, LeftChild(parentIndx).value_or(parentIndx), RightChild(parentIndx).value_or(parentIndx)};
    type_t values[SUB_TREE_SIZE] = {array[parentIndx-1], array[indxArr[1]-1], array[indxArr[2]-1]};
    type_t maxKey;
    size_t i;
    int64_t max_i = parentIndx;

    maxKey = array[parentIndx-1];
    for (i = 1; i < SUB_TREE_SIZE; ++i) {
        if (values[i] > maxKey) {
            maxKey = values[i];
            max_i = indxArr[i];
        }
    }
    return max_i;
}

template <typename type_t>
int64_t Heap<type_t>::findMinIndex(int64_t parentIndx) const noexcept {
    if(parentIndx > (heapSize >> 1)) parentIndx;
    int64_t indxArr[SUB_TREE_SIZE] = {parentIndx, LeftChild(parentIndx).value_or(parentIndx), RightChild(parentIndx).value_or(parentIndx)};
    type_t values[SUB_TREE_SIZE] = {array[parentIndx-1], array[indxArr[1]-1], array[indxArr[2]-1]};
    type_t minKey;
    size_t i; 
    int64_t min_i = parentIndx;

    minKey = array[parentIndx-1];
    for (i = 1; i < SUB_TREE_SIZE; ++i) {
        if (values[i] < minKey) {
            minKey = values[i];
            min_i = indxArr[i];
        }
    }
    return min_i;
}

template <typename data_t>
std::optional<int64_t> Heap<data_t>::Parent(int64_t i) const noexcept {
    if ((i >= 2) & (i <= this->heapSize)) {
        return {i >> 1};
    }
    return {}; // return empty optional
}

template <typename data_t>
std::optional<int64_t> Heap<data_t>::LeftChild(int64_t i) const noexcept {
    if ((i > 0) & (i < ((this->heapSize >> 1) + 1)) & ((2*i) <= this->heapSize)) {
        return 2*i;     
    }
    return {};
}

template <typename data_t>
std::optional<int64_t> Heap<data_t>::RightChild(int64_t i) const noexcept {
    if ((i > 0) & (i < ((this->heapSize >> 1) + 1)) & (((2*i)+1) <= this->heapSize)) {
        return (2*i) + 1;     
    }
    return {};
}

template <typename data_t>
void Heap<data_t>::MaxHeapify(int64_t i) noexcept {
    // assumes that the sub-trees at the left and right child nodes are 
    // max-heaps or hold the max-heap property. Now it must verify that 
    // array[i] holds that same property with respect to it's left and right children, but 
    // that check may invalidate one sub-tree, hence we recursively call it.
    if ((i > 0) & (i <= (this->heapSize >> 1))) {
        auto maxElemIdx = findMaxIndex(i);
        if (maxElemIdx != i) {
            std::swap(array[maxElemIdx-1], array[i-1]);
            MaxHeapify(maxElemIdx);
        }
    }
}

template <typename data_t>
void Heap<data_t>::MinHeapify(int64_t i) noexcept {
    // assumes that the sub-trees at the left and right child nodes are 
    // min-heaps or hold the min-heap property. Now it must verify that 
    // array[i-1] holds that same property with respect to it's left and right children, but 
    // that check may invalidate one sub-tree, hence we recursively call it.
    if ((i > 0) & (i <= (this->heapSize >> 1))) {
        auto minElemIdx = findMinIndex(i);
        if (minElemIdx != i) {
            std::swap(array[minElemIdx-1], array[i-1]);
            MinHeapify(minElemIdx);
        }
    }
}

template <typename data_t>
void Heap<data_t>::BuildHeap() noexcept {
    if (this->type == HeapType::MAX_HEAP) {
        for (size_t i = this->heapSize >> 1; i > 0; --i) {
            MaxHeapify(i);
        }
    } else {
        for (size_t i = heapSize >> 1; i > 0; --i) {
            MinHeapify(i);
        }
    }
}

template <typename data_t>
void Heap<data_t>::InsertHeap(data_t insertElement) {
    array.push_back(insertElement);
    ++this->heapSize;
    int i = heapSize;
    if (this->type == HeapType::MAX_HEAP) {
        while ((i > 0) & (array[i/2 - 1] < array[i-1])) {
            std::swap(array[i-1], array[(i/2) -1]);
            i >>= 1;
        }
    } else {
        while ((i > 1) & (array[(i/2)-1] > array[i-1])) {
            std::swap(array[i-1], array[(i/2) - 1]);
            i >>= 1;
        }
    }
}

// heap-sort is about sorting the internal array, not the heap itself
template<typename data_t>
void Heap<data_t>::MaxHeapSort() noexcept {
    for (;this->heapSize > 0;) {
        std::swap(array[0], array[heapSize-1]);
        --this->heapSize;
        MaxHeapify(1); // keep the maximum at the root of the tree, preserve max-heap property for 1 to heapsize
    }
}

// heap-sort is about sorting the internal array, not the heap itself
template<typename data_t>
void Heap<data_t>::MinHeapSort() noexcept {
    for (;this->heapSize > 1; --this->heapSize) {
        std::swap(array[0], array[heapSize-1]); 
        --this->heapSize;
        MinHeapify(1); // keep the minimum at the root of the tree, preserve min-heap property
    }
}

template<typename data_t>
void Heap<data_t>::HeapDeleteElement(int64_t i) noexcept {
    if ((i > 0) & (i <= this->heapSize)) {
        std::swap(array[i-1], array[heapSize-1]);
        --this->heapSize;
        this->type == HeapType::MAX_HEAP ? this->MaxHeapify(i) : this->MinHeapify(i);
    }
}

template <typename data_t>
bool Heap<data_t>::changeElement(data_t data, data_t new_data) const noexcept {
    bool ret = false;
    int64_t indx;
    for (int i = 0; i < this->heapSize; ++i) {
        if(data == this->array[i]) {
            ret = true;
            indx = i;
            ++indx;
            break;
        }
    }
    if (ret) {
        data[indx-1] = new_data;
        this->BuildHeap();
    }
    return ret;
}

#endif
