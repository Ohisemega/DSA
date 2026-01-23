#include "graph.h"
#include <queue>
/** Khan's BFS Algorithm for Topological Sorting
 * For Directed Graphs
 */

void top_sort(Graph& G, std::vector<int>& res){
    std::array<int, MAX+1> in_degrees;
    in_degrees.fill(0);

    for(int i = 0; i < MAX+1; ++i){
        edgeNode* itr = G.getList()[i];
        while(itr != nullptr){
            ++in_degrees[itr->y];
            itr = itr->next;
        }
    }
    std::queue<int> qu;
    for(int i = 0; i < MAX+1; ++i){
        if(in_degrees[i] == 0) qu.push(i);
    }
    
    while(!qu.empty()){
        int top = qu.front();
        res.push_back(top);
        qu.pop();
        edgeNode* itr = G.getList()[top];
        while(itr != nullptr){
            --in_degrees[itr->y];
            if(in_degrees[itr->y] == 0) qu.push(itr->y);
            itr = itr->next;
        }
    }
    if(res.size() < MAX) res.clear(); 
}
