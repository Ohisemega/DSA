#include "graph.h"
#include <queue>
#include <tuple>

using Node_ID = int;
using Weight = int;
using heap_obj = std::tuple<Weight, Node_ID, Node_ID>;

struct less_hobj{
    bool operator()(heap_obj& a, heap_obj& b){
        return std::get<0>(a) < std::get<0>(b);
    }
};

std::vector<std::pair<Node_ID, Node_ID>> prim_alg_init(Graph& G, int Root, int& t_cost){
    std::priority_queue<heap_obj, std::vector<heap_obj>, less_hobj> min_cost_heap;
    std::array<int, MAX+1> distance;
    std::array<bool, MAX+1> in_tree; //
    G.states[Root] = NodeState::DISCOVERED;
    int total_cost = 0;
//  std::unordered_set<int> visited; // A data structure that allow O(1) time complexity for checking 
    std::vector<std::pair<Node_ID, Node_ID>> MST; // Minimum Spanning Tree!
    edgeNode* itr = nullptr;
    in_tree[Root] = true;

    for(edgeNode* itr = G.getList()[Root]; itr != nullptr; itr = itr->next){
        min_cost_heap.push(heap_obj(itr->weight, Root, itr->y));
    }

    while(!min_cost_heap.empty()){
        heap_obj my_min = min_cost_heap.top(); // get the minimum edge!
        min_cost_heap.pop(); // pop the minimum edge
        if(G.states[std::get<2>(my_min)] == NodeState::UNDISCOVERED){ // If the child node of the edge is UNDISCOVERED 
            G.states[std::get<2>(my_min)] = NodeState::DISCOVERED; // set it to DISCOVERED
            MST.push_back(std::pair(std::get<1>(my_min), std::get<2>(my_min))); // Add the EDGE to the Minimum Spanning Tree
            distance[std::get<2>(my_min)] = std::get<0>(my_min); // set the distance to node y to be the weight of node y in the distance array
            total_cost += std::get<0>(my_min); // update the total cost (it's an accumulating value)!
            for(edgeNode* itr = G.getList()[std::get<2>(my_min)]; itr != nullptr; itr = itr->next){ // explore the neighbors of the child node
                    if(G.states[itr->y] == NodeState::UNDISCOVERED){ // If the neighbors are in an UNDISCOVERED state, add them to the heap
                        min_cost_heap.push(heap_obj(itr->weight, std::get<2>(my_min), itr->y));
                    }
            } // Loop over the heap!
        }
    }
    t_cost = total_cost;
    return MST;
}

/** This algorithm has similarities with BFS, but study and understand it!**/
