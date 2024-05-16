#ifndef P_QUEUE
#define P_QUEUE
#include "heap.hpp"

// class that defines the key-data pairs utilize this class to create your elements on the heap
template<typename data_t>
struct Pobject{
    Pobject(){
        key = -1;
    }
    int key;
    data_t data;
};

template<typename type_t>
class PriorityQueue : public Heap<Pobject<type_t>>{
    private:
       
    public:
        using Heap<type_t>::Heap;
        virtual ~PriorityQueue() = default;
        void Insert(Pobject<type_t>);
        std::pair<type_t, bool> MaxMin_mum() const;
        std::pair<type_t, bool> ExtractMaxMin_mum();
        void HeapDeleteElement(int64_t i);
        bool IncreaseKey(int indx, int key);
        bool DecreaseKey(int indx, int key);
};

template<typename data_t>
void PriorityQueue<data_t>::Insert(Pobject<data_t> obj){
    Heap<Pobject<data_t>>::InsertHeap(obj);
}

template<typename data_t>
std::pair<data_t, bool> PriorityQueue<data_t>::MaxMin_mum() const{
    std::pair<data_t, bool> obj = Heap<Pobject<data_t>>::getElement(1);
    return std::make_pair(obj.first.data, obj.second);
}

template<typename data_t>
std::pair<data_t, bool> PriorityQueue<data_t>::ExtractMaxMin_mum(){
    auto obj = Heap<Pobject<data_t>>::getElement(1);
    Heap<data_t>::HeapDeleteElement(1);
    return std::make_pair(obj.first.data, obj.second);
}

template<typename data_t>
bool PriorityQueue<data_t>::IncreaseKey(int indx, int key){
    return Heap<Pobject<data_t>>::HeapIncreaseKey(indx, key);
}

template<typename data_t>
bool PriorityQueue<data_t>::DecreaseKey(int indx, int key){
    return Heap<Pobject<data_t>>::HeapDecreaseKey(indx, key);
}

template<typename data_t>
void PriorityQueue<data_t>::HeapDeleteElement(int64_t i){
    Heap<Pobject<data_t>>::HeapDeleteElement(i);
}
#endif