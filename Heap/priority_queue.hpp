#ifndef P_QUEUE
#define P_QUEUE
#include "heap.hpp"

// class that defines the key-data pairs utilize this class to create your elements on the heap
template<typename data_t>
struct Pobject{
    int key;
    data_t data;
};

template<typename type_t>
class PriorityQueue : public Heap<type_t>{
    private:
       
    public:
        using Heap<type_t>::Heap;
        virtual ~PriorityQueue() = default;
        void Insert();
        std::pair<type_t, bool> MaxMin_mum() const;
        type_t ExtractMaxMin_mum();
        void HeapDeleteElement(int64_t i);
        void IncreaseKey(type_t x, int key);
        void DecreaseKey(type_t x, int key);
};

template<typename data_t>
void PriorityQueue<data_t>::Insert(){

}

template<typename data_t>
std::pair<data_t, bool> PriorityQueue<data_t>::MaxMin_mum() const{
    std::pair<data_t, bool> obj = Heap<data_t>::getElement(1);
    return std::make_pair(obj.first.data, obj.second);
}

template<typename data_t>
data_t PriorityQueue<data_t>::ExtractMaxMin_mum(){
    std::pair<data_t, bool> obj = Heap<data_t>::getElement(1);
    Heap<data_t>::HeapDeleteElement(1);
    return std::make_pair(obj.first.data, obj.second);
}

template<typename data_t>
void PriorityQueue<data_t>::IncreaseKey(data_t x, int key){

}

template<typename data_t>
void PriorityQueue<data_t>::DecreaseKey(data_t x, int key){

}

template<typename data_t>
void PriorityQueue<data_t>::HeapDeleteElement(int64_t i){
    Heap<data_t>::HeapDeleteElement(i);
}
#endif