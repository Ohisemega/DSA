#include <iostream>
#include <stack>
#include "linked_list.hpp"

int main(){
    List::Linked_list<int> list1;
    List::Linked_list<int> list2;

    list1.putItem(2); // end node of list
    list1.putItem(4);
    list1.putItem(5);
    list1.putItem(3);
    list1.putItem(21);
    list1.putItem(31);
    list1.putItem(83);
    list1.putItem(12);
    list1.putItem(7);
    list1.putItem(71); 
    list1.putItem(45); // list beginning

    std::cout << "The middle of the linked list is: " << list1.getMiddle()->data << "\n";
    std::cout << "The len of the linked list is:";
    list1.isEvenOrOdd() ? std::cout << " Even.\n" : std::cout << " Odd.\n"; 
    list2.putItem(32);
    list2.putItem(47);
    list2.putItem(20);
    list2.putItem(52);
    list2.putItem(34);

    List::Node<int>* node2 = list2.getNode(-1);
    List::Node<int>* node1 = list1.getNode(6);
    node2->next = node1;
    std::cout << "The merging point is: " << node1->data << "\n";

    std::stack<List::Node<int>*> stck1;
    std::stack<List::Node<int>*> stck2;
    for (int i = 0; ; ++i){
        if(list1.getNode(i) == nullptr){
            break;
        }else{
            stck1.push(list1.getNode(i));
            std::cout << "The list1 node just pushed is: " << list1.getNode(i)->data << "\n";
        }
    }

    for (int i = 0; ; ++i){
        if(list2.getNode(i) == nullptr){
            break;
        }else{
            stck2.push(list2.getNode(i));
            std::cout << "The list2 node just pushed is: " << list2.getNode(i)->data << "\n";
        }
    }
     
    List::Node<int>* temp;
    while(stck1.top() == stck2.top()){
        temp = stck1.top();
        stck1.pop();
        stck2.pop();
    }
    std::cout << "The merging point is: " << temp->data << "\n";
    node2->next = nullptr;

    List::Linked_list<int> sort1;
    List::Linked_list<int> sort2;
    sort1.putItem(83); // end node of list 
    sort1.putItem(71);
    sort1.putItem(45);
    sort1.putItem(31);
    sort1.putItem(21);
    sort1.putItem(12);
    sort1.putItem(7);
    sort1.putItem(5);
    sort1.putItem(4);
    sort1.putItem(3);
    sort1.putItem(2);// list beginning



    sort2.putItem(98); // end node of list
    sort2.putItem(87);
    sort2.putItem(64);
    sort2.putItem(59);
    sort2.putItem(32);
    sort2.putItem(12);
    sort2.putItem(11);
    sort2.putItem(10); // list beginning

    sort1.MergeSorted(sort2);
    sort1.printList();


}