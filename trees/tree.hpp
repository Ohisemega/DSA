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
    Tree(int val, Tree* left, Tree* right){
        this->left = left;
        this->right = right;
        this->val = val;
    }
};

template <typename K, typename T>
struct Tree_t {
    Tree_t* left;
    Tree_t* right;
    K key;
    T val;

    explicit Tree_t(K key, T val){
        this->left = this->right = nullptr;
        this->val = val;
        this->key = key;
    }
    Tree_t(T val, Tree_t* left, Tree_t* right) {
        this->left = left;
        this->right = right;
        this->val = val;
    }
};

template <typename T, size_t SZ = sizeof(T)>
inline bool bit_val(T val, const int idx) {
    static_assert(idx < SZ);
    return bool((1 << idx) & val);
}

inline void visit(Tree* node){
    std::cout << node->val << "\n";
}
