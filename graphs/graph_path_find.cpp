/** Finding the Shortest path in a graph between two nodes: x (start) & y (end),
 * can be achieved by using the BFS algorithm to build an array of the parent node
 * IDs for every child ID (the array's index).
 * But the BFS MUST be built using x's ID as the root node to work!
 * Secondly, the graph MUST be UNWEIGHTED for this to work! 
 */

#include "graph.h"

using NodeID = int;
void find_path(NodeID start, NodeID end, NodeID parents[]) {
    if(start == end || start == -1) {
        std::cout << '\n' << start << '\n';
    }else{
        find_path(start, parents[end], parents);
        std::cout << '\n' << end << '\n';
    }

}
