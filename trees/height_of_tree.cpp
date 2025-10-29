#include "tree.hpp"
#include <queue>

int max_tree_depth_recursive(Tree* root){
    if(root == nullptr){
        return  -1; // we return -1 because our depth algorithm assumes that every function call automatically
                    // adds depth level +1 to the tree's height. i.e. line 8
    }
    int u = max_tree_depth_recursive(root->left);
    int v = max_tree_depth_recursive(root->right);
    return (u > v ? u + 1 : v + 1);
}


// This uses a BFS algorithm to find the height of the tree
// We use a 'nullptr' to demacate each level
int max_tree_depth_iterative(Tree* node){
    std::queue<Tree*> que;
    Tree* current = node;
    int height = -1;
    if(node == nullptr) return height;
    
    que.emplace(node);
    que.emplace(nullptr);


    while(!que.empty()){
        current = que.front();
        que.pop();

        if(current == nullptr){
            ++height;

            if(!que.empty()){
                que.emplace(nullptr);
            }            
        }
        
        if(current->left){
            que.emplace(current->left);
        }
        if(current->right){
            que.emplace(current->right);
        }
    }

    return height;
}
