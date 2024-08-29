#include "tree.hpp"

bool is_isomorphic_btrees(Tree* t1, Tree* t2){
    if(t1 == nullptr && t2 == nullptr){
        return true;
    }

    if(t1 == nullptr || t2 == nullptr){
        return false;
    }

    if(t1->val != t2->val){ // if the values at this node are not the same, then return a negative already
        return false;
    }

    // if the values checkout, then the trees are isomorphic up till this node.
    // Now check the two possible cases of isomorphism, (r1->r2, l1->l2) or (r1->l2, l1->r2)
    // where r1 and l1 are right and left child nodes of the same subtree and r2 and l2 are same for the other subtree
    return (is_isomorphic_btrees(t1->right, t2->right) && is_isomorphic_btrees(t1->left, t2->left)) || \
            (is_isomorphic_btrees(t1->right, t2->left) && is_isomorphic_btrees(t1->left, t2->right));
}