#include "graph.h"
#include <queue>

void process_node_early(int node) {
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
        G.states[top] = NodeState::DISCOVERED;
        process_node_early(top);

        for(edgeNode* itr = G.getList()[top]; itr != nullptr; itr = itr->next) {
            if(G.states[itr->y] == NodeState::UNDISCOVERED) {
                G.states[itr->y] = NodeState::DISCOVERED;
                G.parents[itr->y] = top;
                Qu.push(itr->y);
            }else if(G.states[itr->y] != NodeState::PROCESSED) {
                process_edge(top, itr->y);
            }
        }
        G.states[top] = NodeState::PROCESSED;

    }
}

