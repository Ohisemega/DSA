#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H
#include <cstdint>
#include <utility>
template <typename t>
class Queue_Array{
    private:
        t* array;
        // tail is ALWAYS at an empty index at the end of the queue
        // head is positioned at the oldest item on the queue
        // --- except at initialization, when head = size + 1
        // interestingly, the last index of the array array[size + 1]
        // never contains an item, because:
        // for tail, it never 'stays' on it (tail % arraySize) to "put"
        // an item
        // for head, it never 'stays' on it (head % arraySize) to 'get'
        // an item 
        // the MODULO '%' sign ensures this!

        std::uint64_t head, tail;
        std::uint64_t arraySize;
    public:
        Queue_Array(uint64_t size){
            arraySize = size+1;
            array = new t[size + 1];
            head =  arraySize;
            tail = 0;
        }

        virtual ~Queue_Array(){
            delete [] array;
        }

        std::pair<t, bool> get(){
            std::pair<t, bool> retPair;
            retPair.second = isEmpty() ? false : true;
            head  %= arraySize;
            return array[head++];
        }

        bool put(t item){
            bool ret;
            if(tail + 1 == head){
                ret = false; // queue is full
            }else{
                array[tail++] = item;
                tail %= arraySize;
                ret = true;
            }
            return ret;
        }

        bool isEmpty() const{
            return (head % arraySize) == 0;
        }
};

#endif