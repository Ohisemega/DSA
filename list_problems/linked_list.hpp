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
            void MergeSorted(Linked_list<Item>& l2_sorted);
            bool isEvenOrOdd() const;
            std::pair<Item, bool> get();
            void printList() const;
            void reversePairs();
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

    template <typename type_t> // This assumes that this* linked list is sorted
    void Linked_list<type_t>::MergeSorted(Linked_list<type_t>& l2_sorted) {
        if(l2_sorted.isEmpty()) return;
        if(this->isEmpty()){
            this->dummyHead.next = l2_sorted.dummyHead.next;
            l2_sorted.dummyHead.next = nullptr;
            return;
        }

        Node<type_t>* prev1 = &this->dummyHead;
        Node<type_t>* itr1 = this->dummyHead.next;
        Node<type_t>* itr2 = l2_sorted.dummyHead.next;
        
        // merge smallest to largest (ascending -  1, 2, 3, 4, ...)
        while(itr1 != nullptr && itr2 != nullptr){
            Node<type_t>* temp;
            if(itr1->data > itr2->data){ 
                prev1->next = itr2; // make the prev pointer's next on the main line linked list point to the item to be inserted behind the current pointer
                temp = itr2->next; // cache the next pointer of itr2 as it will be updated
                itr2->next = itr1; // make itr2's next pointer point to the linked list of 'this'
                itr2 = temp; // update itr2 back to it's original list
                prev1 = prev1->next;
            }else{
                prev1 = itr1;
                itr1 = itr1->next;
            }
        }
        l2_sorted.dummyHead.next = nullptr;
    }

    template <typename type_t> // This assumes that this* linked list is sorted
    void Linked_list<type_t>::printList() const {
        Node<type_t>* itr = this->dummyHead.next;
        while (itr->next != nullptr){
            std::cout << itr->data << " ";
            itr = itr->next;               
        }
    }

    template <typename type_t> // This assumes that this* linked list is sorted
    void Linked_list<type_t>::reversePairs() {
        Node<type_t>* itr = this->dummyHead.next;
        Node<type_t>* itr2;
        Node<type_t>* temp;
        Node<type_t>* prev = &this->dummyHead;
        while (itr != nullptr && itr->next != nullptr){ //||_b_||-> 1* -> 2 -> 3 -> ...nullptr 
            temp = itr->next->next; // cache the value of itr->next->next
            itr2 = itr->next; // cache 
            itr->next = temp;
            itr2->next = itr;

            prev->next = itr2;
            prev = itr;
            itr = temp;
        }
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