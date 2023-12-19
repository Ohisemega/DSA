#include <utility>
#include <cstdint>
#include <iostream>

#ifndef DEQUE_HPP
#define DEQUE_HPP
namespace deque_template{
    template <typename type_t>
    class Deque{
        public:
            // Deque();
            Deque(int32_t maxN=10);
            ~Deque();
            bool isEmpty() const;
            bool push_back(type_t);
            bool push_front(type_t);
            std::pair<type_t, bool> pop_back();
            std::pair<type_t, bool> pop_front();
            std::pair<type_t, bool> at(int32_t)const;
            void clear();
            std::pair<type_t, bool> front() const;
            std::pair<type_t, bool> back() const;
            void printArray() const;

        private:
            void defaultDeque();
            int32_t maxSize, head, tail, itemCount;
            type_t q[10]; // pointer to hold array location
            
    };

    template <typename type_t>
    void Deque<type_t>::printArray()const{
        for(int i = 0; i < maxSize; ++i){
            std::cout << q[i] << ", ";
        }
        std::cout << "\n";
    }

    template <typename type_t>
    Deque<type_t>::Deque(int32_t maxN){
        maxSize = 10;
        // q = new type_t[maxN];
        head = maxSize - 1;
        itemCount = tail = 0;
    }

    template <typename type_t>
    Deque<type_t>::~Deque(){
        // delete[] q;
        clear();
    }

    template<typename type_t>
    void Deque<type_t>::defaultDeque(){
        if(itemCount == 0){
            head = maxSize - 1;
            tail = 0;
        }
    }

    template <typename type_t>
    bool Deque<type_t>::isEmpty()const{
        return itemCount == 0;
    }

    template <typename type_t>
    bool Deque<type_t>::push_front(type_t item){
        bool ret = false;
        // std::cout << "About to push the item!\n";
        if((head != 0) && (itemCount != maxSize-1)){
            q[head--] = item;
            ret = true;
            ++itemCount;
        }else if((head == 0) && (tail != maxSize-1)){
            head = maxSize-1;
            q[head--] = item;
            ret = true;
            ++itemCount;
        }
        return ret;
    }

    template <typename type_t>
    std::pair<type_t, bool> Deque<type_t>::pop_front(){
        std::pair<type_t, bool> retPair;
        retPair.second = false;
        
        if(!isEmpty()){  
            if(head != maxSize-1){
            retPair.first = q[++head];
            }else{
                head = 0;
                retPair.first = q[head];
            }
            retPair.second = true;
            --itemCount;
        }else{
            defaultDeque();
        }
        return retPair;
    }

    template <typename type_t>
    bool Deque<type_t>::push_back(type_t item){
        bool ret = false;
        if((tail != maxSize-1) && (itemCount != maxSize-1)){
            q[tail++] = item;
            ret = true;
            ++itemCount;
        }else if((tail == maxSize-1) && (head != 0)){
            tail = 0;
            q[tail++] = item;
            ret = true;
            ++itemCount;
        }
        return ret;
    }

    template <typename type_t>
    std::pair<type_t, bool> Deque<type_t>::pop_back(){
        std::pair<type_t, bool> retPair;
        retPair.second = false;
        if(!isEmpty()){
            if(tail != 0){
                retPair.first = q[--tail];
            }else{
                tail = maxSize-1;
                retPair.first = q[tail];
            }
            retPair.second = true;
            --itemCount;
        }else{
            defaultDeque();
        }
        return retPair;
    }

    template <typename type_t>
    std::pair<type_t, bool> Deque<type_t>::at(int32_t index) const{
        std::pair<type_t, bool> retPair;
        retPair.second = false;
        if(!isEmpty() && (index <= itemCount)){
            if((head + index) <= maxSize-1){
                retPair.first = q[head + index];
            }else{
                int32_t indx = (head+index) % maxSize;
                retPair.first = q[indx - 1];
            }
            retPair.second = true;
        }
        return retPair;
    }

    template <typename type_t>
    void Deque<type_t>::clear(){
        head = tail;
        itemCount = maxSize = 0;
    }
}
#endif