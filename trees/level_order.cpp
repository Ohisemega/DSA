#include "tree.hpp"
#include <queue>

void Level_order_traversal_iterative(Tree* root){
    std::queue<Tree*> que;
    Tree* current = root;
    que.emplace(current);
    while(!que.empty()){
        current = que.back();
        que.pop();
        visit(current);
        que.emplace(current->left);
        que.emplace(current->right);
    }
}