#include <utility>
#include <iostream>
#ifndef FIFO_CIR_LIST
#define FIFO_CIR_LIST

namespace List{
    template<typename nd>
    struct Node{
        Node<nd>* next;
        nd data;

        Node(){
            next = nullptr;
        }

        Node(nd m_data){
            data = m_data;
            next = nullptr;
        }

        // insert after node next_n
        Node(nd m_data, Node<nd>* next_n){
            data = m_data;
            next = next_n->next;
        }
    };

    template <typename Item>
    class Linked_list{
        private:
            Node<Item> dummyHead;
        
        public:
            Linked_list();
            virtual ~Linked_list();
            bool isEmpty() const;
            void putItem(Item);
            Node<Item>* getNode(int = -1) const;
            Node<Item>* getMiddle() const;
            bool isEvenOrOdd() const;
            std::pair<Item, bool> get();
    };

    template <typename type_t>
    Linked_list<type_t>::Linked_list(){
        dummyHead.next = nullptr;
    }

    template <typename type_t>
    Linked_list<type_t>::~Linked_list(){
        Node<type_t>* itr = dummyHead.next;
        while (itr != nullptr)
        {
            dummyHead.next = dummyHead.next->next;
            delete itr;
            itr = nullptr;
            itr = dummyHead.next;
        }
    }

    template <typename type_t>
    bool Linked_list<type_t>::isEmpty() const{
        return (dummyHead.next == nullptr);
    }

    template <typename type_t>
    Node<type_t>* Linked_list<type_t>::getNode(int indx) const{
        Node<type_t>* itr = dummyHead.next;
        if(isEmpty()) return nullptr;
        if(indx == -1){
            while (itr->next != nullptr){
                itr = itr->next;               
            }
        }else{
            int count = 0;
            while (count < indx && itr->next != nullptr){
                itr = itr->next;
                ++count;      
            }
            if (count != indx){
                itr = nullptr;
            }
        }
        // std::cout << "The iterator's data is: " << itr->data << std::endl;
        return itr;
    }

    template <typename type_t>
    Node<type_t>* Linked_list<type_t>::getMiddle() const{
        Node<type_t>* fitr = dummyHead.next;
        Node<type_t>* sitr = dummyHead.next;

        if(isEmpty()) return nullptr;

        while(fitr != nullptr && fitr->next != nullptr){
            fitr = fitr->next->next;
            sitr = sitr->next;
        }

        return sitr;
    }

    template <typename type_t>
    bool Linked_list<type_t>::isEvenOrOdd() const{
        Node<type_t>* fitr = dummyHead.next;
        Node<type_t>* sitr = dummyHead.next;

        if(isEmpty()) return true;

        while(fitr != nullptr && fitr->next != nullptr){
            fitr = fitr->next->next;
            sitr = sitr->next;
        }

        if(fitr){
            return false;
        }

        return true;
    }


    template <typename type_t>
    void Linked_list<type_t>::putItem(type_t item){
        dummyHead.next = new Node<type_t>(item, &dummyHead);
    }

    template <typename type_t>
    std::pair<type_t, bool> Linked_list<type_t>::get(){
        std::pair<type_t, bool> retPair;
        retPair.second = false;
        if(!isEmpty()){
            Node<type_t>* rem = dummyHead.next;
            retPair.first = rem->data;
            retPair.second = true;
            dummyHead.next = dummyHead.next->next;
            delete rem;
            rem = nullptr;
        }
        return retPair;
    }
}

#endif