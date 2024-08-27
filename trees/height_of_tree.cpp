#include "tree.hpp"

int max_tree_depth_recursive(Tree* root){
    if(root == nullptr){
        return  -1; // we return -1 because our depth algorithm assumes that every function call automatically
                    // adds depth level +1 to the tree's height. i.e. line 8
    }
    int u = max_tree_depth_recursive(root->left) + 1;
    int v = max_tree_depth_recursive(root->right) + 1;
    return (u > v ? u : v);
}