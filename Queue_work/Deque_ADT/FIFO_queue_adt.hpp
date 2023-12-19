#include <utility>
#ifndef FIFO_CIR_LIST
#define FIFO_CIR_LIST

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
    }
    return retPair;
}


#endif