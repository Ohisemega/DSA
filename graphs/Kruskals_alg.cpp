#include "graph.h"
#include <vector>
#include <algorithm>
#include <unordered_set>

int kruskal_alg(Graph& G, std::vector<std::pair<int, int>> MST ){
    int total_cost = 0;
    std::unordered_set<int> in_mst_set;
    using cost = int;
    std::vector<std::tuple<cost, int, int>> sorted_cost_arr;
    sorted_cost_arr.reserve(G.vertices() + 16);
    G.states.fill(NodeState::UNDISCOVERED);
    for(int i = 0; i <= G.vertices(); ++i) {
        G.states[i] = NodeState::DISCOVERED;
        for(edgeNode* itr = G.getList()[i]; itr != nullptr; itr = itr->next) {
            if(G.states[itr->y] == NodeState::UNDISCOVERED && !G.is_directed()) sorted_cost_arr.push_back(std::tuple(itr->weight, i, itr->y));
            else if(G.is_directed()) sorted_cost_arr.push_back(std::tuple(itr->weight, i, itr->y));
        }
    }
    G.states.fill(NodeState::UNDISCOVERED);
    std::sort(sorted_cost_arr.begin(), sorted_cost_arr.end());
    for(int i = 0; i < sorted_cost_arr.size(); ++i) {
        if(in_mst_set.count(std::get<1>(sorted_cost_arr[i])) == 0 || in_mst_set.count(std::get<2>(sorted_cost_arr[i])) == 0){
           // If either of the nodes of this edge is NOT in the in_mst_set/visited set, then add this edge to the MST!
            total_cost += std::get<0>(sorted_cost_arr[i]);
            MST.push_back(std::pair(std::get<1>(sorted_cost_arr[i]), std::get<2>(sorted_cost_arr[i])));
            in_mst_set.insert(std::get<1>(sorted_cost_arr[i]));
            in_mst_set.insert(std::get<2>(sorted_cost_arr[i]));
        }
    }
    return total_cost; // return the total cost of the MST from kruskal
}
