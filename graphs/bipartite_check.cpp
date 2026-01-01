/** The algorithm for detecting if a given Graph
 * Can be color labelled to become a BIPARTITE
 * GRAPH!
 */

#include "graph.h"

enum class Colour {
    UNCOLOURED = 0,
    BLACK = 1,
    WHITE = 2,
};
using Root = int;
std::array<Colour, MAX+1> bipartite_colours;
void BFS_traversal(Graph& G, Root vtx);

bool is_biparite_graph(Graph& G) {
    bool is_bipartite_v = true;
    bipartite_colours.fill(Colour::UNCOLOURED);
    G.initialize();
    for(int i = 1; i < G.vertices(); ++i) {
        bipartite_colours[i] = Colour::WHITE;

        if(G.states[i] == NodeState::UNDISCOVERED) {
            bipartite_colours[i] = Colour::WHITE;
            BFS_traversal(G, i);
        }
    }
    return is_bipartite_v;
}

Colour complement(Colour cl) {
    if(cl == Colour::BLACK) {
        return Colour::WHITE;
    }
    if(cl == Colour::WHITE) {
        return Colour::BLACK;
    }
    return Colour::UNCOLOURED;
}

void process_edge(int parent, int child, bool& is_bipartite){
    if(bipartite_colours[parent] == bipartite_colours[child]){
        is_bipartite = false;
        std::cout << "Graph CANNOT be bipartite because parent and child have same color\n";
    }
    bipartite_colours[child] = complement(bipartite_colours[parent]);
}
