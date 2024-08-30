#include "tree.hpp"

Tree* tournament_construction(int arr[], int beg, int end){
    if(beg == end) return new Tree(arr[beg]); // base case

    int mid = (beg + end) << 1;
    Tree* node = nullptr;
    node->right = tournament_construction(arr, mid+1, end);
    node->left = tournament_construction(arr, beg, mid);
    if(node->right->val > node->left->val){
        node = new Tree(node->right->val, node->right, node->left);
    }else{
        node = new Tree(node->left->val, node->right, node->left);
    }
    return node;
}