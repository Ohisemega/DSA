#include "graph.h"

enum class NodeState{
    UNDISCOVERED = 0,
    DISCOVERED = 2,
    PROCESSED = 4,
};

#include <array>
#include <queue>

std::array<NodeState, MAX+1> states;
std::array<int, MAX+1> parents;

void process_node_early(int node){
    std::cout << "Processed Node is: " << node << '\n';
}

void process_edge(int parent, int child) {
    std::cout << "Processed Edge: " << parent << " " << child << '\n';
}

using Root = int;
void BFS_traversal(Graph& G, Root vtx) {
    std::queue<int> Qu;
    Qu.push(vtx);
    while(!Qu.empty()) {
        int top = Qu.front();
        Qu.pop();
        states[top] = NodeState::DISCOVERED;
        process_node_early(top);

        for(edgeNode* itr = G.getList()[top]; itr != nullptr; itr = itr->next) {
            if(states[itr->y] == NodeState::UNDISCOVERED) {
                states[itr->y] = NodeState::DISCOVERED;
                parents[itr->y] = top;
                Qu.push(itr->y);
            }else if(states[itr->y] != NodeState::PROCESSED) {
                process_edge(top, itr->y);
            }
        }
        states[top] = NodeState::PROCESSED;

    }
}

