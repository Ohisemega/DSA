#include <utility>
#include <cstdint>

#ifndef DEQUE_LIST_HPP
#define DEQUE_LIST_HPP
namespace deque_template{

    template<typename nd>
    struct Node{
        Node<nd>* next;
        Node<nd>* prev;
        nd data;

        Node(){
            next = nullptr;
            prev = nullptr;
        }

        Node(nd m_data) : Node{}{
            data = m_data;
        }

        // insert after node next_n
        Node(nd m_data, Node<nd>* next_n){
            data = m_data;
            next = next_n->next;
            prev = next_n;
        }

        // insert before node next_n
        Node(Node<nd>* prev_n, nd m_data){
            data = m_data;
            next = prev_n;
            prev = prev_n->prev;
        }
    };

    template <typename type_t>
    class Deque{
        public:
            Deque();
            virtual ~Deque();
            bool isEmpty() const;
            void push_back(type_t);
            void push_front(type_t);
            std::pair<type_t, bool> pop_back();
            std::pair<type_t, bool> pop_front();
            std::pair<type_t, bool> at(int32_t indx)const;
            void clear();
            // void insert();
            std::pair<type_t, bool> front() const;
            std::pair<type_t, bool> back() const;

        private:
            Node<type_t> dummyHead;
            Node<type_t> dummyTail;           
    };

    template <typename type_t>
    Deque<type_t>::Deque(){
        dummyHead.next = &dummyTail;
        dummyTail.next = nullptr;
        dummyTail.prev = &dummyHead;
        dummyHead.prev = nullptr;        
    }

    template <typename type_t>
    Deque<type_t>::~Deque(){
        this->clear();
    }

    template <typename type_t>
    bool Deque<type_t>::isEmpty()const{
        return (dummyHead.next == &dummyTail);
    }

    template <typename type_t>
    void Deque<type_t>::push_front(type_t item){
        dummyHead.next->prev = new Node<type_t>(item, &dummyHead);
        dummyHead.next = dummyHead.next->prev;
    }

    template <typename type_t>
    void Deque<type_t>::push_back(type_t item){
        dummyTail.prev->next = new Node<type_t>(&dummyTail, item);
        dummyTail.prev = dummyTail.prev->next;
    }

    template <typename type_t>
    std::pair<type_t, bool> Deque<type_t>::pop_front(){
        std::pair<type_t, bool> retPair;
        retPair.second = false;
        if(!isEmpty()){
            retPair.first = dummyHead.next->data;
            retPair.second = true;
            Node<type_t>* rem = dummyHead.next; // store the pointer to next;
            dummyHead.next->next->prev = &dummyHead; // set the prev pointer of the node after the next node to the dummyHead to dummyHead itself
            dummyHead.next = dummyHead.next->next; 
            delete rem;
            rem = nullptr;
        }
        return retPair;
    }

    template <typename type_t>
    std::pair<type_t, bool> Deque<type_t>::pop_back(){
        std::pair<type_t, bool> retPair;
        retPair.second = false;
        if(!isEmpty()){
            retPair.first   = dummyTail.prev->data;
            retPair.second  = true;
            Node<type_t>* rem   = dummyTail.prev;
            dummyTail.prev->prev->next = &dummyTail;
            dummyTail.prev = dummyTail.prev->prev;
            delete rem;
            rem = nullptr;
        }
        return retPair;
    }

    template <typename type_t>
    std::pair<type_t, bool> Deque<type_t>::at(int32_t indx) const{
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
    void Deque<type_t>::clear(){
        for(Node<type_t>*itr = dummyHead.next; itr != &dummyTail; itr = itr->next){
            delete itr;
            itr = nullptr;
        }
    }
    
    template <typename type_t>
    std::pair<type_t, bool> Deque<type_t>::front() const{
        std::pair<type_t, bool> retPair;
        retPair.second = false;
        retPair.first  = dummyHead.next->data;
        if(!isEmpty()){
            retPair.second  = true;
        }
        return retPair;
    }

    template <typename type_t>
    std::pair<type_t, bool> Deque<type_t>::back() const{
        std::pair<type_t, bool> retPair;
        retPair.second = false;
        retPair.first  = dummyTail.prev->data;
        if(!isEmpty()){
            retPair.second  = true;
        }
        return retPair;
    }
}
#endif