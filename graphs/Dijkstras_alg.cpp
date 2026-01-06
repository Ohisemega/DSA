#include "graph.h"
#include <limits>
#include <queue>
//

int Dijkstra_alg(Graph& G, int start, int dest, std::vector<std::vector<int>> sp/*where to store the shortest path*/){
    std::array<int, MAX+1> cmin_costs; // array of the minimum cost - for node-i, we have found so far from start----to--->i.
    cmin_costs.fill(std::numeric_limits<int>::max()); // initialize all costs to be 'infinitely expensive'
    cmin_costs[0] = 0; // we however know that the cost from start----to---->start IS EQUAL to 0
    G.initialize();
    using cost = int; // aliasing int with the name 'cost'
    using p_node = int; // data type of parent node IDs
    using ch_node = int; // data type of child node IDs
    using heap_obj = std::tuple<cost, p_node, ch_node>;

    struct greater_hobj{
        bool operator()(heap_obj& a, heap_obj& b){
            return std::get<0>(a) > std::get<0>(b);
        }
    };

    std::priority_queue<heap_obj, std::vector<heap_obj>, greater_hobj> min_heap;
    for(edgeNode* itr = G.getList()[start]; itr != nullptr; itr = itr->next){
        min_heap.push(std::tuple(itr->weight + cmin_costs[start],  start, itr->y));
        G.parents[itr->y] = start;
        cmin_costs[itr->y] = itr->weight + cmin_costs[start];
    }
    G.states[start] = NodeState::DISCOVERED;
    int shortest_path_cost = 0;

    while(!min_heap.empty()){
        heap_obj top = min_heap.top(); // explore next smallest town!
        min_heap.pop();
        ch_node child = std::get<2>(top);

        // update the child's min travel cost if this current edge has a better option!
        if(cmin_costs[child] > std::get<0>(top)){
            cmin_costs[child] = std::get<0>(top);
            G.parents[child] = std::get<1>(top);
            shortest_path_cost += cmin_costs[child];
            sp.push_back({std::get<1>(top), child});
        }

        if(G.states[child] == NodeState::UNDISCOVERED){
            G.states[child] = NodeState::DISCOVERED;
            for(edgeNode* itr = G.getList()[child]; itr != nullptr; itr = itr->next){
                if(cmin_costs[itr->y] > (cmin_costs[child] + itr->weight)){
                    cmin_costs[itr->y] = cmin_costs[child] + itr->weight; // update the current known min cost to get to itr->y as we have found a smaller one!
                    G.parents[itr->y] = child; // since itr->y has a new min travel cost on this edge, it's new parent is child!
                }
                if(G.states[itr->y] == NodeState::UNDISCOVERED){
                    min_heap.push(std::tuple(cmin_costs[itr->y], child, itr->y));
                }
            } 
        } 
    }
}
