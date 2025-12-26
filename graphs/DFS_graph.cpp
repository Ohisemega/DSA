

/** DFS, unlike BFS, actually has a natural recursive implementation
 * A DFS traversal is traversing the first 'sub-graph' accessible 
 * when we read/process the first child node adjacent to the ROOT node
 * We keep trying to access the next deeper sub-graph till we hit a NULL
 * point and then we 'backtrack' to the last node, and access the next 
 * adjacent "child node" in a DFS manner too!
 */

/** The DFS algorithm works by iterating from the given ROOT node
 *  to the 1st next adjacent "UNEXPLORED" node, processing it,
 *  and then running the same algorithm on that node
 *  A node is fully PROCESSED when we have gone through all it's
 *  adjacent neighbours.
 *  A node is DISCOVERED when we find it on an adjacency list!
 *  An edge between a parent and node is processed() when we 
 *  encounter a child in the adjacency list!
 *
 *  We use a STACK to simulate delayed computation,
 *  But in using a stack, we push the first UNDISCOVERED
 *  node to the bottom of the stack. To mimic the Recursion
 *  model, we actually want to visit the node at the bottom
 *  of the STACK! Hence, we can use a DEQUEUE, and access the 
 *  oldest element on the QUEUE/DEQUE rather that the recently 
 *  pushed one allowed by the STACK data structure!
 */
#include "graph.h"
#include <stack>
#include <deque>
#include <vector>

void DFS_traversal(Graph& G, int Root, int time[MAX+1]){
    std::stack<int> stk;
    std::vector<int> vec;
    vec.reserve(64);
    std::deque<int> deq;
    deq.push_back(Root);
    edgeNode* itr = nullptr;
    G.states[Root] = NodeState::DISCOVERED;
    while(!deq.empty()) {
        int top = stk.top();
        stk.pop();
        
        if(G.states[top] == NodeState::PROCESSED) continue;

        for(itr = G.getList()[top]; itr != nullptr; itr = itr->next) {
            if(G.states[itr->y] == NodeState::UNDISCOVERED){
                G.states[itr->y] = NodeState::DISCOVERED;
                G.parents[itr->y] = top;
                vec.push_back(itr->y);
                process_edge_early(top, itr->y); // do we want to process the edge early?!!
            }else if((G.states[itr->y] == NodeState::DISCOVERED && G.parents[itr->y] != top) || G.is_directed()) {
                process_edge_late(top, itr->y);
            }
        }
        for(int i = vec.size(); i >= 0; --i) {
            stk.push(vec[i]);
        }
        vec.clear();
        G.states[top] = NodeState::PROCESSED;
    }
}


void DFS_traversal_rec(Graph& G, int Root, int time[MAX+1]) {
    edgeNode* itr = nullptr;
    itr = G.getList()[Root];
    while(itr != nullptr){
        if(G.states[itr->y] == NodeState::UNDISCOVERED){
            G.states[itr->y] = NodeState::DISCOVERED;
            G.parents[itr->y] = Root;
            DFS_traversal_rec(G, Root, time);
            process_edge_early(Root, itr->y);
        }else if((G.states[itr->y] != NodeState::PROCESSED && G.parents[itr->y] != Root) || (G.is_directed())){
            process_edge_late(Root, itr->y);
        }
        G.states[Root] = NodeState::PROCESSED;
        itr = itr->next;
    }
}

