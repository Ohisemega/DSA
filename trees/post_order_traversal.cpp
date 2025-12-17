#include "tree.hpp"
#include <stack>
#include <vector>

void PostOrder_traversal_recursive(Tree* root){
    if(root != nullptr){
        if(root->left) PostOrder_traversal_recursive(root->left);
        if(root->right) PostOrder_traversal_recursive(root->right);
        visit(root);
    }
}

void PostOrder_traversal_iterative(Tree* root){
    std::vector<bool> visited = {0};
    std::stack<Tree*> stck;
    if(root == nullptr) return;
    Tree* current = root;
    while(!stck.empty() || current != nullptr){
        while(current != nullptr){
            stck.push(current);
            current = current->left;
        }
        // at this point, current is definitely null meaning no more left children exist
        // so we check the stack's top value to go up one tree level
        current  = stck.top();

        /* here we are checking if the current (non-null) 
            node has a right-child, if so we must visit 
            it first because this is a post-order traversal
      */if(current->right){ 
            current = current->right;
        }else{ /* otherwise we can finally visit this current node 
                    (because trees are recursive so leaf nodes have trivial 
                    null-children we use to check the leafiness of each node)
                    meaning null left and right children allow us to visit a node
                */
            visit(current);
            stck.pop();
            if(stck.top()->right == current){
                visit(stck.top());
                stck.pop();
            }
            current = stck.top()->right; // this should set current as null here
        }
    }
}
