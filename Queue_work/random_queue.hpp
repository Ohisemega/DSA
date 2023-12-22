#ifndef RANDOM_QUEUE
#define RANDOM_QUEUE

#include <utility>
#include <cstdint>
#include <random> // to be imolemented
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace rand_queue_template{
    template <typename type_t>
    class RandomQueue{
        public:
            RandomQueue(uint32_t maxN=50);
            ~RandomQueue();
            bool isEmpty() const;
            uint32_t size() const;
            uint32_t capacity() const;
            bool enque(type_t);
            std::pair<type_t, bool> dequeue();
            std::pair<type_t, bool> sample();
            void clear();
            
            void printArray() const;

        private:
            uint32_t generateRandom()const;
            uint32_t maxSize, head, tail, itemCount;
            type_t* q;
    };

    template <typename type_t>
    void RandomQueue<type_t>::printArray()const{
        for(int i = 0; i < maxSize; ++i){
            std::cout << q[i] << ", ";
        }
        std::cout << "\n";
    }

    template <typename type_t>
    RandomQueue<type_t>::RandomQueue(uint32_t maxN){
        maxSize = maxN + 1;
        q = new type_t[maxSize];
        head = maxSize;
        itemCount = tail = 0;
        std::srand(time(0));
    }

    template <typename type_t>
    RandomQueue<type_t>::~RandomQueue(){
        delete[] q;
        q = nullptr;
        clear();
    }

    template<typename type_t>
    uint32_t RandomQueue<type_t>::generateRandom()const{
        // ought to implement a C++ <random> library 
        return (rand() % this->maxSize);
    }

    template <typename type_t>
    std::pair<type_t, bool> RandomQueue<type_t>::dequeue(){
        std::pair<type_t, bool> retPair;
        uint32_t index;
        head  %= maxSize;
        retPair.second = isEmpty() ? false : true;
        uint32_t randomPoint = generateRandom() % this->itemCount;
        index = (head+randomPoint) % maxSize;
        retPair.first = q[index];
        q[index] = q[head++];
        --itemCount;
        return retPair;
    }

    template <typename type_t>
    std::pair<type_t, bool> RandomQueue<type_t>::sample(){
        std::pair<type_t, bool> retPair;
        uint32_t index;
        head  %= maxSize;
        retPair.second = isEmpty() ? false : true;
        uint32_t randomPoint = generateRandom() % this->itemCount;
        index = (head+randomPoint) % maxSize;
        retPair.first = q[index];
        return retPair;
    }

    template <typename type_t>
    bool RandomQueue<type_t>::isEmpty()const{
        return ((head % maxSize) == tail) || (itemCount == 0);
    }

    template <typename type_t>
    uint32_t RandomQueue<type_t>::size() const{
        return maxSize;
    }

    template <typename type_t>
    bool RandomQueue<type_t>::enque(type_t item){
        bool ret;
        if(tail + 1 == head){
            ret = false; // queue is full
        }else{
            q[tail++] = item;
            tail %= maxSize;
            ret = true;
        }
        ++itemCount;
        return ret;
    }

    template <typename type_t>
    void RandomQueue<type_t>::clear(){
        head = tail;
        itemCount = maxSize = 0;
    }
}

#endif