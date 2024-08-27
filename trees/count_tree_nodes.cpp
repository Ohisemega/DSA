#include "tree.hpp"

int count_tree_nodes(Tree* root){
    if(root == nullptr) return 0;

    return 1 + count_tree_nodes(root->left) + count_tree_nodes(root->right);
}
/*An iterative solution to this algorithm would be to use one of the traversal methods and increment a global counter!*/