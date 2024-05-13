#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP
#include <cstdint>
#include <utility>
#include <algorithm>
#include <iostream>
template <class Item>
class STACK{
    private:
        Item *s;
        uint32_t N, maxCapacity;

    public:
        STACK(){
            N = maxCapacity = 0;
            s = nullptr;
        }

        explicit STACK(int32_t maxN){
            this->maxCapacity = maxN;
            this->s = new Item[maxN];
            this->N  = 0;
        }

        STACK(const STACK &) = delete; // delete the copy constructor
        
        STACK(STACK&& mvObj) noexcept : maxCapacity(mvObj.maxCapacity), N(mvObj.N), s(mvObj.s) { // move constructor
            mvObj.s = nullptr;
            mvObj.maxCapacity = mvObj.N = 0;
        }

        virtual ~STACK(){
            N = maxCapacity = 0;
            if(this->s){
                delete[] s;
            }
        }

        STACK& operator=(const STACK<Item>& cpyAssObj){
            if(this->s){
                delete[] this->s;
            }
            this->maxCapacity = cpyAssObj.maxCapacity;
            this->s = new Item[maxCapacity];
            this->N  = cpyAssObj.N;
            std::copy(cpyAssObj.s, cpyAssObj.s + cpyAssObj.N, this->s);
            return *this;
        }

        STACK& operator=(STACK<Item>&& mvObject) noexcept{
            if(&mvObject == this)
                return *this;
            maxCapacity = mvObject.maxCapacity;
            N = mvObject.N;
            s = mvObject.s;
            mvObject.s = nullptr;
            mvObject.maxCapacity = mvObject.N = 0;
            return *this;
        }
        
        bool empty()const{
            return N == 0;
        }

        std::pair<Item, bool> pop(){
            std::pair<Item, bool> retPair;
            retPair.second  = false;
            if(!empty()){
                retPair.second = true;
                retPair.first = s[N--];
            }
            return retPair;
        }

        bool push(Item item){
            int32_t count = 0;
            bool isPresent = false, retVal = false;
            for(int i = 0; i < N; ++i){
                if(s[i] == item){
                    isPresent = true;
                    break;
                }
            }
            if(!isPresent && N < maxCapacity){
                s[N++] = item;
                retVal = true;
            }
            return retVal;
        }

        void reverseStackOrder(){

        }

        void printIntArray() const{
            
            for (size_t i = 0; i < N; ++i){
                std::cout << s[i] << ", ";
            }
            std::cout << "\n";
        }
};

#endif