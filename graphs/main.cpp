#include "graph.h"
// include "DFS.h"

void DFS_module_init();
void DFS_traversal(Graph& G, int Root, bool& is_cycle);

int main(){
    Graph G{true, 6, 7};
    G.initialize();
    G.read_graph();
    bool is_cycle = false;
    DFS_module_init();
    DFS_traversal(G, 0, is_cycle);
}
