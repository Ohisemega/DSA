#ifndef P_QUEUE
#define P_QUEUE
#include "heap.hpp"

// class that defines the key-data pairs utilize this class to create your elements on the heap
template<typename data_t>
struct Pobject{
    Pobject(){
        key = -1;
    }
    Pobject(int key){
        this->key = key;
    }
    Pobject(data_t data, int key){
        this->key = key;
        this->data = data;
    }

    bool operator<(const Pobject<data_t>& obj) const noexcept{
        return this->key < obj.key;
    }
    bool operator>(const Pobject<data_t>& obj) const noexcept{
        return this->key > obj.key;
    }
    bool operator==(const Pobject<data_t>& obj) const noexcept{
        return this->key == obj.key;
    }
    private:
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
        std::pair<type_t, bool> Maximum() const noexcept;
        std::pair<type_t, bool> Minimum() const noexcept;
        std::pair<type_t, bool> ExtractMax();
        std::pair<type_t, bool> ExtractMin();
        void HeapDeleteElement(int64_t i);
        bool IncreaseKey(int indx, int key);
        bool DecreaseKey(int indx, int key);
        HeapType getPriorityQueueType() const noexcept; 
};

template<typename data_t>
void PriorityQueue<data_t>::Insert(Pobject<data_t> obj){
    Heap<Pobject<data_t>>::InsertHeap(obj);
}

template<typename data_t>
HeapType PriorityQueue<data_t>::getPriorityQueueType() const noexcept{
    return Heap<Pobject<data_t>>::getHeapType();
}

template<typename data_t>
std::pair<data_t, bool> PriorityQueue<data_t>::Maximum() const noexcept{
    std::pair<Pobject<data_t>, bool> obj = Heap<Pobject<data_t>>::getElement(1);
    if(Heap<Pobject<data_t>>::getHeapType() == HeapType::MIN_HEAP) obj.second = false;
    return std::make_pair(obj.first.data, obj.second);
}

template<typename data_t>
std::pair<data_t, bool> PriorityQueue<data_t>::Minimum() const noexcept{
    std::pair<Pobject<data_t>, bool> obj = Heap<Pobject<data_t>>::getElement(1);
    if(Heap<Pobject<data_t>>::getHeapType() == HeapType::MAX_HEAP) obj.second = false;
    return std::make_pair(obj.first.data, obj.second);
}

template<typename data_t>
std::pair<data_t, bool> PriorityQueue<data_t>::ExtractMax(){
    auto obj = Heap<Pobject<data_t>>::getElement(1);
    Heap<data_t>::HeapDeleteElement(1);
    return std::make_pair(obj.first.data, obj.second);
}

template<typename data_t>
std::pair<data_t, bool> PriorityQueue<data_t>::ExtractMin(){
    auto obj = Heap<Pobject<data_t>>::getElement(1);
    Heap<data_t>::HeapDeleteElement(1);
    return std::make_pair(obj.first.data, obj.second);
}

template<typename data_t>
bool PriorityQueue<data_t>::IncreaseKey(int indx, int key){
    bool ret = false;
    if(Heap<Pobject<data_t>>::getElement(indx).second && Heap<Pobject<data_t>>::getElement(indx) > Pobject<data_t>(key) && Heap<Pobject<data_t>>::getHeapType() == HeapType::MAX_HEAP){
        Pobject<data_t> temp{Heap<Pobject<data_t>>::getElement(indx)};
        temp.key = key;
        Heap<Pobject<data_t>>::getElement(indx) = temp;
        Heap<Pobject<data_t>>::HeapIncreaseKey(indx);
        ret = true;
    }
    return ret;
}

template<typename data_t>
bool PriorityQueue<data_t>::DecreaseKey(int indx, int key){
    bool ret = false;
    if(Heap<Pobject<data_t>>::getElement(indx).second && Heap<Pobject<data_t>>::getElement(indx) < Pobject<data_t>(key) && Heap<Pobject<data_t>>::getHeapType() == HeapType::MIN_HEAP){
        Pobject<data_t> temp{Heap<Pobject<data_t>>::getElement(indx)};
        temp.key = key;
        Heap<Pobject<data_t>>::getElement(indx) = temp;
        Heap<Pobject<data_t>>::HeapDecreaseKey(indx);
        ret = true;
    }
    return ret;
}

template<typename data_t>
void PriorityQueue<data_t>::HeapDeleteElement(int64_t i){
    Heap<Pobject<data_t>>::HeapDeleteElement(i);
}
#endif