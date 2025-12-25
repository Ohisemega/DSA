#include "graph.h"
#include <queue>

/** process_node_early() and process_edge() methods describe what the 
 *  BFS algorithm does to the vertices and edges. If the methods do nothing, 
 *  the BFS algorithm simply chnages the "states[]" array and the "parents[]" 
 *  array, but does nothing to the 'edges' or 'nodes'.
 *
 *  Processing a vertex may be as simple as printing the vertex's ID
 *  Or as complex as changing it's edge connection or direction(s)
 *  Processing an edge may be as simple as printing the edge's vertices
 *  or as complex as changing a property of the associated vertices.
 */

void process_node_early(int node) {
    std::cout << "Processed Node is: " << node << '\n';
}

void process_edge(int parent, int child) {
    std::cout << "Processed Edge: " << parent << " " << child << '\n';
}

/** The BFS algorithm is to take an arbitrary ROOT node, and 
 * put it in a QUEUE data structure, then pop the oldest item
 * in the QUEUE and iterate through all it's adjacent nodes
 * by pushing them in the queue, and processing their edges!
 * if they are in an UNDISCOVERED state
 */

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
            }else if(G.states[itr->y] != NodeState::PROCESSED || G.is_directed()) { // It is in NodeState::DISCOVERED !
                process_edge(top, itr->y);
            }
        }
        G.states[top] = NodeState::PROCESSED;

    }
}

