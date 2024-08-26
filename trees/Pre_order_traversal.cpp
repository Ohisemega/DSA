#include "tree.hpp"
#include <iostream>
#include <stack>

void PreOrder_trvaersal_recursive(Tree* root){
    if(root != nullptr){
        visit(root);
        PreOrder_trvaersal_recursive(root->left);
        PreOrder_trvaersal_recursive(root->right);
    }
}

void PreOrder_trvaersal_iterative(Tree*root){
    std::stack<Tree*> call_stck;
    if(root == nullptr) return;

    call_stck.push(root);
    while(!call_stck.empty()){
        Tree* temp = call_stck.top();
        call_stck.pop();
        visit(temp);
        if(temp->right) call_stck.push(temp->right);
        if(temp->left) call_stck.push(temp->left);
    }
}