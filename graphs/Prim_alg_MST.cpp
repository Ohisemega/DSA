/** What is PRIM's Algorithm **/
/** It is used to find the Minimum Spanning Tree and it's total cost in a graph! **/
/*
1. Given a Graph representation (either an adjacency list or a set of edges, or an adjacency square-matrix)
2. Given a Root node in that graph (or choosing one at random).
3. Set the TOTAL_COST variable of the MST to be 0!
4. Iterate through ALL neighbors of the root:
5.      Add the edge-pairs (with their associated cost-value) to a minimum heap aka MIN PRIORITY QUEUE.
6. <WHILE> the MIN PRIORITY QUEUE is not empty:
7.      Pop the top element or edge-pair in the MIN PRIORITY QUEUE.
8.      <IF> the 1st element of the edge-pair is in UNDISCOVERED state:
9.          Set the state of 1st-element-of-pair to be DISCOVERED / VISITED.
10.          Add the edge-pair to the list of edges in the MST vector.
11.         Update the TOTAL_COST variable of the MST.
12.         Iterate through ALL neighbours of the 2nd-element-of-pair.
13.             <IF> the 2nd element is in UNDISCOVERED state:
14.                 Add the edge-pair with their associated cost to the MIN PRIORITY QUEUE.
15. Loop to STEP 5!
*/

#include "graph.h"
#include <queue>
#include <tuple>
#include <unordered_set>

using Node_ID = int;
using Weight = int;
using heap_obj = std::tuple<Weight, Node_ID>;

struct greater_hobj{
    bool operator()(heap_obj& a, heap_obj& b){
        return std::get<0>(a) > std::get<0>(b);
    }
};

std::vector<std::pair<Node_ID, Node_ID>> prim_alg(Graph& G, int Root, int& t_cost){
    std::priority_queue<heap_obj, std::vector<heap_obj>, greater_hobj> min_cost_heap;
    G.states[Root] = NodeState::DISCOVERED;
    int total_cost = 0;
//  std::unordered_set<int> visited; // A data structure that allow O(1) time complexity for checking 
    std::vector<std::pair<Node_ID, Node_ID>> MST; // Minimum Spanning Tree!
    MST.reserve(MAX);
    edgeNode* itr = nullptr;
    std::unordered_set<int> vert_set; // a set DS to track all nodes tha have been added to the Minimum Spanning Tree 

    min_cost_heap.push({0, Root});
    vert_set.insert(Root);
    while(!min_cost_heap.empty()){
        if(G.vertices() == vert_set.size()) break; // all vertices are in the MST! 
        heap_obj my_min = min_cost_heap.top(); // get the minimum edge!
        min_cost_heap.pop(); // pop the minimum edge
        Node_ID node = std::get<1>(my_min);
        if(G.states[node] == NodeState::UNDISCOVERED){ // If the child node of the edge is UNDISCOVERED 
            G.states[node] = NodeState::DISCOVERED; // set it to DISCOVERED
            MST.push_back(std::pair(G.parents[node], node)); // Add the EDGE to the Minimum Spanning Tree
            vert_set.insert(node); // add the child node to the known set of vertices in the MST                                      
            total_cost += std::get<0>(my_min); // update the total cost (it's an accumulating value)!
            for(edgeNode* itr = G.getList()[node]; itr != nullptr; itr = itr->next){ // explore the neighbors of the child node
                if(G.states[itr->y] == NodeState::UNDISCOVERED){ // If the neighbors are in an UNDISCOVERED state, add them to the heap
                    G.parents[itr->y] = node;
                    min_cost_heap.push(heap_obj(itr->weight,itr->y));
                }
            } // Loop over the heap!
        }
    }
    t_cost = total_cost;
    return MST;
}

/** This algorithm has similarities with BFS, but study and understand it!**/
