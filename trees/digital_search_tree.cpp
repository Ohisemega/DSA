#include "tree.hpp"
#include <type_traits>


template <typename T>
constexpr T nullItem;

// handles only unique keys!
template <typename T, typename V>
class DST {
    using Key = T;
    using Value = V;
    Tree_t<Key, Value>* head;
    static constexpr T nullItem;

    T search_r(Tree_t<Key, Value>* node, Key k, int bit_idx) {
        if(!node) return nullItem;
        if(node->key == k) return node->val;
        if(bit_idx(k, bit_idx)) search_r(node->right, k, bit_idx+1);
        else search_r(node->left, k, bit_idx+1);
    }

    Tree_t<Key, Value>* insert_u_r(Tree_t<Key, Value>* node, Key k, Value v, int idx) {
        if(!node) return new(Tree_t(k, v));
        if(node->key == k) return node;
        if(bit_idx(k, bit_idx)) return node = insert_r(node->right, k, bit_idx+1);
        else return node = insert_r(node->left, k, bit_idx+1);
    }

    Tree_t<Key, Value>* insert_r(Tree_t<Key, Value>* node, Key k, Value v, int idx) {
        if(!node) return new(Tree_t(k, v));
        if(node->key == k) {
            node->val = val;
            return node;
        }
        if(bit_idx(k, bit_idx)) return node = insert_r(node->right, k, bit_idx+1);
        else return node = insert_r(node->left, k, bit_idx+1);
    }

    public:
        DST() : head{nullptr}{}
        V search(Key k) {
            return search_r(head, k, 0);
        }

        Tree_t<Key, Value>* insert(Key k, Value v) {
            insert_r(head, k, v, 0);
        }

        Tree_t<Key, Value>* insert_u(Key k, Value v) {
            insert_r_u_r(head, k, v, 0);
        }
};
