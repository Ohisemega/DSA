#include <iostream>
// template<typename type_t>
struct Tree{
    Tree* left;
    Tree* right;
    int val;

    explicit Tree(int val){
        this->left = this->right = nullptr;
        this->val = val;
    }
    explicit Tree(int val, Tree* left, Tree* right){
        this->left = left;
        this->right = right;
        this->val = val;
    }
};

inline void visit(Tree* node){
    std::cout << node->val << "\n";
}