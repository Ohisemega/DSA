#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP
#include <cstdint>
#include <utility>
#include <memory>
#include <iostream>
#include <stdexcept>

template <typename Item>
class STACK{
    private:
        std::unique_ptr<Item> s;
        int N, maxCapacity;
        void InsertAtBottom(Item data){
            Item tempData;
            if(this->empty()){
                push(data);
                return;
            }

            tempData = this->top().first;
            this->pop();
            this->InsertAtBottom(data);
            this->push(tempData);
        }

    public:
        STACK(){
            maxCapacity = 10;
            N = -1;
            s = std::unique_ptr<Item>{new Item[maxCapacity]};
        }

        explicit STACK(int32_t maxN){
            if(maxN <= 0){
                throw std::length_error{std::string("Stack size is < 0!\n")};
            }
            s = std::unique_ptr<Item>{new Item[maxN]};
            this->maxCapacity = maxN;
            this->N  = -1;
        }

        STACK(const STACK &) = delete; // delete the copy constructor
        
        STACK(STACK&& mvObj) noexcept : maxCapacity(mvObj.maxCapacity), N(mvObj.N), s(mvObj.s) { // move constructor
            mvObj.s = nullptr;
            mvObj.maxCapacity = 0;
            mvObj.N = -1;
        }

        virtual ~STACK(){
            maxCapacity = 0;
            this->N  = -1;
        }

        // STACK& operator=(const STACK<Item>& cpyAssObj){
        //     if(this->s){
        //         delete[] this->s;
        //     }
        //     this->maxCapacity = cpyAssObj.maxCapacity;
        //     this->s = new Item[maxCapacity];
        //     this->N  = cpyAssObj.N;
        //     std::copy(cpyAssObj.s, cpyAssObj.s + cpyAssObj.N, this->s);
        //     return *this;
        // }

        STACK& operator=(STACK<Item>&& mvObject) noexcept{
            if(&mvObject == this)
                return *this;
            maxCapacity = mvObject.maxCapacity;
            N = mvObject.N;
            s = std::move(mvObject.s);
            mvObject.s = nullptr;
            mvObject.maxCapacity = mvObject.N = 0;
            return *this;
        }
        
        bool empty()const{
            return N < 0;
        }

        std::pair<Item, bool> top() const{
            std::pair<Item, bool> retPair;
            retPair.second  = false;
            if(!this->empty()){
                retPair.second = true;
                retPair.first = s[N];
            }
            return retPair;
        }

        void pop() noexcept{
            if(!this->empty()){
                N--;
            }
        }

        bool push(Item item){
            int32_t count = 0;
            bool isPresent = false, retVal = false;
            for(int i = 0; i <= N; ++i){
                if(s[i] == item){
                    isPresent = true;
                    break;
                }
            }
            if(!isPresent && N < maxCapacity){
                s[++N] = item;
                retVal = true;
            }
            return retVal;
        }

        void reverseStackOrder(){
            if(this->empty()) return;

            Item data;
            data = this->top().first;
            this->pop();
            reverseStackOrder();
            InsertAtBottom(data);
        }

        void printIntArray() const{
            for (int i = 0; i <= N; ++i){
                std::cout << s[i] << ", ";
            }
            std::cout << "\n";
        }
};

#endif