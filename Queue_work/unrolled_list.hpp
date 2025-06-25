#include <utility>
#include <cstdint>
#include <vector>

#ifndef UNROLLED_LIST_HPP
#define UNROLLED_LIST_HPP
namespace Unrolled_List_template{

    template <typename Data_t>
    struct block_data{
        std::vector<Data_t> data; // pointer to data array
    };


    template <typename Data_t>
    class Unrolled_List{
        public:
            Unrolled_List();
            virtual ~Unrolled_List();
            bool isEmpty() const;
            void clear();
            void insert();
            std::pair<Data_t, bool>at(int32_t indx) const; // find and return object at index
            bool find(Data_t data); // find object in 
            std::pair<Data_t, bool> front() const;
            std::pair<Data_t, bool> back() const;

        private:
            block_data<Data_t> head;
            Unrolled_List* next;
    };

    template <typename type_t>
    Unrolled_List<type_t>::Unrolled_List(){
        this->next = nullptr;
        count = 0;
        this->data = nullptr;
    }

    template <typename type_t>
    Unrolled_List<type_t>::~Unrolled_List(){
        this->clear();
    }

    template <typename type_t>
    bool Unrolled_List<type_t>::isEmpty()const{
        return (dummyHead.next == &dummyTail);
    }

    template <typename type_t>
    std::pair<type_t, bool> Unrolled_List<type_t>::at(int32_t indx) const{
        Node<type_t>*itr = dummyHead.next;
        std::pair<type_t, bool> retPair;
        retPair.second = false;
        int32_t count = 0;
        while (itr != &dummyTail && count < indx)
        {
            itr = itr->next;
            ++count;
        }

        if(count == indx){
            retPair.first = itr->data;
            retPair.second = true;
        }
        return retPair;
    }

    template <typename type_t>
    void Unrolled_List<type_t>::clear(){
        for(Node<type_t>*itr = dummyHead.next; itr != &dummyTail; itr = itr->next){
            delete itr;
            itr = nullptr;
        }
    }
}
#endif