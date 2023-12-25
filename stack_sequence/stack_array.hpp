#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP
#include <cstdint>
#include <utility>
#include <iostream>
template <class Item>
class STACK{
    private:
        Item *s;
        Item *duplicate; 
        uint32_t N, maxCapacity;

    public:
        STACK(int32_t maxN){
            maxCapacity = maxN;
            s = new Item[maxN];
            duplicate = new Item[maxN];
            N  = 0;
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
            for(int i =0; i < N; ++i){
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

        void printIntArray(){
            
            for (size_t i = 0; i < N; ++i){
                std::cout << s[i] << ", ";
            }
            std::cout << "\n";
        }
        
        
};

#endif