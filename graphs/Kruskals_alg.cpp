#include "graph.h"
#include <vector>
#include <algorithm>

int kruskal_alg(Graph& G, std::vector<std::pair<int, int>> MST ){
    int total_cost = 0;
    using cost = int;
    std::vector<std::tuple<cost, int, int>> sorted_cost_arr;
    UnionFind UF;
    UF.initialize();
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
        std::tuple<bool, int, int> temp = UF.is_same_tree(std::get<1>(sorted_cost_arr[i]), std::get<1>(sorted_cost_arr[i]));
        if(!std::get<0>(temp)){
            UF.union_alg(std::get<1>(temp), std::get<2>(temp));
            total_cost += std::get<0>(sorted_cost_arr[i]);
            MST.push_back(std::pair(std::get<1>(sorted_cost_arr[i]), std::get<2>(sorted_cost_arr[i])));
        }
        if(UF.getMaxTreeSize() == G.vertices()) break; // we have added all the vertices in the Graph into a single tree in the UF algorithm!
    }
    return total_cost; // return the total cost of the MST from kruskal
}
