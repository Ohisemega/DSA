#include "tree.hpp"
#include <iostream>
#include <stack>

void InOrder_trvaersal_recursive(Tree* root){
    if(root != nullptr){
        InOrder_trvaersal_recursive(root->left);
        visit(root);
        InOrder_trvaersal_recursive(root->right);
    }
}

void InOrder_trvaersal_iterative(Tree* root){
    std::stack<Tree*> stk;
    Tree* curr = root;
    while (curr != nullptr || !stk.empty()){
        while(curr != nullptr){
            stk.push(curr);
            curr = curr->left;
        }
        curr = stk.top();
        visit(curr);
        stk.pop();
        curr = curr->right;
    }    
}