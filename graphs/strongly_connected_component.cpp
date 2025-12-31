#include "graph.h"

// This Algorithm uses a BFS_traversal to test if a given vertex has a path to every other vertex in a given graph - G
// If so we say that the Graph is a Strongly Connected Component from the vertex.
// We can run this algorithm for EVERY vertex in the graph by having a higher function call this function for every vertex in a graph
// But not this is a quadratic complexity algorithm as opposed to linear!
//
// for(int i = 1; i < G.vertices(); ++i) {
//      if(!is_SCC_graph(G, i)) return false;
// }
// return true;
void BFS_traversal(Graph&, int);
//
bool is_SCC_graph(Graph& G, int vertex) {
    G.initialize();
    BFS_traversal(G, vertex);
    for(int i = 1; i < G.vertices(); ++i){
        if(G.states[i] == NodeState::UNDISCOVERED) return false;
    }
    return true;
}
