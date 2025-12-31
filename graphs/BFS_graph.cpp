#include "graph.h"
#include <queue>

/** process_node_early() and process_edge() methods describe what the 
 *  BFS algorithm does to the vertices and edges. If the methods do nothing, 
 *  the BFS algorithm simply chnages the "states[]" array and the "parents[]" 
 *  array, but does nothing to the 'edges' or 'nodes'.
 *
 *  A node's state is only changed to PROCESSED when we have set all it's adjacent
 *  children to a DISCOVERED state!
 *
 *  Processing a vertex may be as simple as printing the vertex's ID
 *  Or as complex as changing it's edge connection or direction(s)
 *  Processing an edge may be as simple as printing the edge's vertices
 *  or as complex as changing a property of the associated vertices.
 */

void process_node_early(Graph& G, int node) {
    std::cout << "Processed Node Early is: " << node << '\n';
}

void process_node_late(Graph& g, int node) {
    std::cout << "Processed Node Late is: " << node << '\n';
}

void process_edge(Graph& g, int parent, int child) {
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
        process_node_early(G,top);

        for(edgeNode* itr = G.getList()[top]; itr != nullptr; itr = itr->next) {
            if(G.states[itr->y] != NodeState::PROCESSED || G.is_directed()) { // It is in NodeState::DISCOVERED !
                process_edge(G, top, itr->y);
            }
            else if(G.states[itr->y] == NodeState::UNDISCOVERED) {
                G.parents[itr->y] = top;
                process_edge(G, top, itr->y); // when we call process_edge() the child's state is still UNDISCOVERED so we can still get a TREE_EDGE!
                G.states[itr->y] = NodeState::DISCOVERED;
                Qu.push(itr->y);
            }
        }
        process_node_late(G,top);
        G.states[top] = NodeState::PROCESSED; // A node is only PROCESSED in a BFS when we have gone through all it's adjacent children!
    }
}

