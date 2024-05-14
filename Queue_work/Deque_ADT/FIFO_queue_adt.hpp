#include <utility>
#include <iostream>
#ifndef FIFO_CIR_LIST
#define FIFO_CIR_LIST

namespace Circular_List{
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
    class QueueCirList{
        private:
            Node<Item> dummyHead;
        
        public:
            QueueCirList();
            virtual ~QueueCirList();
            bool isEmpty() const;
            void putItem(Item);
            bool detect_circular_list() const;
            std::pair<Item, bool> get();
    };

    template <typename type_t>
    QueueCirList<type_t>::QueueCirList(){
        dummyHead.next = &dummyHead;
    }

    template <typename type_t>
    QueueCirList<type_t>::~QueueCirList(){
        Node<type_t>* itr = dummyHead.next;
        while (itr != &dummyHead)
        {
            dummyHead.next = dummyHead.next->next;
            delete itr;
            itr = nullptr;
            itr = dummyHead.next;
        }
    }

    template <typename type_t>
    bool QueueCirList<type_t>::isEmpty() const{
        return (dummyHead.next == &dummyHead);
    }

    template <typename type_t>
    void QueueCirList<type_t>::putItem(type_t item){
        dummyHead.next = new Node<type_t>(item, &dummyHead);
    }

    template <typename type_t>
    std::pair<type_t, bool> QueueCirList<type_t>::get(){
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

    template <typename type_t>
    bool QueueCirList<type_t>::detect_circular_list() const{
        Circular_List::Node<type_t>* itr = dummyHead.next;
        Circular_List::Node<type_t>* itr2 = dummyHead.next;

        while(itr->next != &dummyHead){
            itr = itr->next;
        }
        itr->next = dummyHead.next->next->next->next;
        std::cout << "The round point is: " << itr->next->data << "\n";
        itr = dummyHead.next;
        if(itr->next == &dummyHead){
            return true;
        }

        bool retVal = false;
        while (itr != nullptr && itr2 != nullptr)
        {
            itr = itr->next;
            itr2 = itr2->next->next;
            if(itr == itr2){
                retVal = true;
                std::cout << "the data at the detection point is " << itr2->data << "\n";
                break;
            }
        }

        if(retVal){
            itr = dummyHead.next;
            while (itr != itr2)
            {
                itr = itr->next;
                itr2 = itr2->next;
                if(itr == itr2){
                    std::cout << "the Cycle Start point is: " << itr2->data << "\n";
                    break;
                }
            }
            int cycleLen = 1;
            itr2 = itr2->next;
            while (itr != itr2)
            {
                itr2 = itr2->next;
                if(itr == itr2){
                    std::cout << "the Cycle length is: " << cycleLen << "\n";
                    break;
                }
                ++cycleLen;
            }

        }
        return retVal;
    }

}

#endif