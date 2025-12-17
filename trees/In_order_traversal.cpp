#include "tree.hpp"
#include <iostream>
#include <stack>

void InOrder_traversal_recursive(Tree* root){
    if(root != nullptr){
        if(root->left) InOrder_traversal_recursive(root->left);
        visit(root);
        if(root->right) InOrder_traversal_recursive(root->right);
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

Tree* InOrder_SUCCESSOR(Tree* root, Tree* target){
    std::stack<Tree*> stk;
    Tree* curr = root;
    Tree* prev = nullptr;
    while (curr != nullptr || !stk.empty()){
        while(curr != nullptr){
            stk.push(curr);
            curr = curr->left;
        }
        curr = stk.top();
        visit(curr);
        if(prev == target) return curr;
        prev = curr;
        stk.pop();
        curr = curr->right;
    }
    return nullptr;
}

Tree* Inorder_successor(Tree* root, int targ_key){
	Tree* prev_left_parent = nullptr;
	Tree* current = root;
	if (!root) return nullptr;	
	// find the target
	int key;
	while (key != targ_key){
		key = current->val;
		if(targ_key < key){
			prev_left_parent = current;
			current = current->left;
		}else if (targ_key > key){
			current  = current->right;
		}else{
			// target does not exist;
			return nullptr;
		}
	}
	
	if(current->right){
		current = current->right;
		while(current->left){
			current = current->left;
		}
		return current; // this is the successor
	}else{
		return prev_left_parent;
	}
}
