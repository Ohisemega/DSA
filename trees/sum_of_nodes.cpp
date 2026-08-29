#include "tree.hpp"

int sum_of_tree(Tree* root){
    if(root == nullptr){
        return 0;
    }
    return sum_of_tree(root->left) + root->val + sum_of_tree(root->right);
}
