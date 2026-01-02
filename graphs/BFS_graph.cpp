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

EdgeClass process_edge(Graph& g, int parent, int child) {
    std::cout << "Processed Edge: " << parent << " " << child << '\n';
    return EdgeClass::NO_EDGE; // dummy implementation, real implementation in in DFS module!
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
            // On first encounter, a node y has NodeState::UNDISCOVERED
            // So the 1sr condition of the if-statement below is TRUE!
            // The 1st condition of the 2nd if-statement is also TRUE! so both run for any UNDISCOVERED child node y relative to parent NODE - top!
            if(G.states[itr->y] != NodeState::PROCESSED || G.is_directed()) { // It is in NodeState::DISCOVERED !
                itr->eclass = process_edge(G, top, itr->y);
            }
            if(G.states[itr->y] == NodeState::UNDISCOVERED) { // A PROCESSED node will fail this condition!
                G.parents[itr->y] = top;
                G.states[itr->y] = NodeState::DISCOVERED;
                Qu.push(itr->y);
            }
        }
        process_node_late(G,top);
        G.states[top] = NodeState::PROCESSED; // A node is only PROCESSED in a BFS when we have gone through all it's adjacent children! And queued all UNDISCOVERED adjacent children
    }
}

