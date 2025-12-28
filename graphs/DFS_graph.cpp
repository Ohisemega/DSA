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
 *  adjacent neighbours. At the end statement of the While loop iteration 
 *  of that node!
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

void process_node_early(Graph& G, int node);
void process_node_late(Graph& G, int node);
bool process_edge_cycle_search(int start, int end, std::array<int, MAX+1>& parents);

std::array<int, MAX+1> entry_time;
std::array<int, MAX+1> exit_time;
std::array<int, MAX+1> reachable_ancestor;
std::array<int, MAX+1> tree_node_degree; /*This is an array that stores the number of TREE-EDGES each node in a GRAPH has during a DFS-Tree generation from some arbitrary root!*/
static int time_cnt = 0;

void DFS_traversal(Graph& G, int Root, bool& is_cycle ){
    std::stack<int> stk;
    std::vector<int> vec;
    vec.reserve(64);
    stk.push(Root);
    edgeNode* itr = nullptr;
    G.states[Root] = NodeState::DISCOVERED;
    is_cycle = false;
    while(!stk.empty()) {
        time_cnt++;
        int top = stk.top();
        stk.pop();
        if(top >= 0) {
            entry_time[top] = time_cnt;
        }else{
            exit_time[top*(-1)] = time_cnt;
            continue;
        }
        
        if(G.states[top] == NodeState::PROCESSED) continue;
        process_node_early(G, top);
        for(itr = G.getList()[top]; itr != nullptr; itr = itr->next) {
            if(G.states[itr->y] == NodeState::UNDISCOVERED){
                G.states[itr->y] = NodeState::DISCOVERED;
                G.parents[itr->y] = top; // TREE-EDGE
                vec.push_back(itr->y);
                process_edge_early(top, itr->y); // do we want to process the edge early?!!
            }else if((G.states[itr->y] == NodeState::DISCOVERED && G.parents[itr->y] != top/*BACK-EDGE*/) || G.is_directed()) {
                process_edge_late(top, itr->y);
                if(G.states[itr->y] == NodeState::DISCOVERED && G.parents[top] != itr->y) is_cycle = true; // This Graph HAS A CYCLE!
            }
        }
        for(int i = vec.size()-1; i >= 0; --i) {
            stk.push(vec[i]);
        }
        stk.push(-top);
        vec.clear();
        process_node_late(G, top);
        G.states[top] = NodeState::PROCESSED;
    }
}

void DFS_traversal_rec(Graph& G, int Root, bool& is_cycle) {
    edgeNode* itr = nullptr;
    itr = G.getList()[Root];
    ++time_cnt;
    entry_time[Root] = time_cnt;
    process_node_early(G, Root);
    while(itr != nullptr){
        if(G.states[itr->y] == NodeState::UNDISCOVERED){
            G.states[itr->y] = NodeState::DISCOVERED;
            G.parents[itr->y] = Root;
            DFS_traversal_rec(G, Root, is_cycle);
            process_edge_early(Root, itr->y);
        }else if((G.states[itr->y] != NodeState::PROCESSED && G.parents[Root] != itr->y) || (G.is_directed())){
            is_cycle = process_edge_cycle_search(Root, itr->y, G.parents);
            process_edge_late(Root, itr->y);
        }
        itr = itr->next;
    }
    G.states[Root] = NodeState::PROCESSED;
    ++time_cnt;
    exit_time[Root] = time_cnt;
    process_node_late(G, Root);
}

void find_path(int start, int end, std::array<int, MAX+1>& parents) {
    if(start == end || start == -1) {
        std::cout << start << '\n';
    }else{
        find_path(start, parents[end], parents);
        std::cout << end << '\n';
    }
}

bool process_edge_cycle_search(int start, int end, std::array<int, MAX+1>& parents) {
    if(parents[start] != end) {
        std::cout << "Cycle detected in Graph between nodes: " << start << " and " << end << '\n';
        find_path(start, end, parents);
        return false;
    }
    return true;
}

void process_node_early(int node) {
    reachable_ancestor[node] = node; // Initially, All nodes are set to be reachable to only themselves by setting 
                                     // reachable_ancestor[node] = node;
                                     // in the process_node_early() method!
}

/* void process_edge() method Given a graph and two nodes
 * This is to support the detection of an ARTICULATION 
 * NODE.
 * The purpose of process_node_early() is simply to
 * Get the EDGE's classification - TREE_EDGE/BACK_EDGE
 * if TREE_EDGE: Increment the tree_node_degree for the DFS-Traversal tree of the GRAPH
 * if EDGE_NODE: Check if y is x's parent, if not, check the earliest ancestor of x! and update the ancestor if y is earlier than x's current earliest ancestor
 *               Do this by checking entry_time[y] is < entry_time[reachable_ancestor[x]]; if so, update reachable_ancestor[x] = y;
 */
void process_edge(Graph& G, int parent, int child) {
    EdgeClass eclass = edge_classification(parent, child);

    if(eclass == EdgeClass::TREE_EDGE) {
        ++tree_node_degree[parent]; // The Tree Edge from the Parent--to-->Child. Here, the Child was in an UNDISCOVERED state, and the Parent is it's direct ancestor automatically!
    }

    if(eclass == EdgeClass::BACK_EDGE && (G.parents[parent] != child)) {
        // Remember that the child is the parent's ancestor in this case
        if(entry_time[child] < entry_time[reachable_ancestor[parent]]) { // If the entry_time[child] is earlier than the entry_time[parent's current reachable ancestor]:
                                                                         // Then we update the parent's reachable ancestor as we have an older one in view now!
            reachable_ancestor[parent] = child;
        }
    }
}

void process_node_late(Graph& G, int node) {
    bool root;
    int time_node;
    int time_parent;

    if(G.parents[node] == -1) {
        if(tree_node_degree[node] > 1) {
            std::cout << "Root articulation vertex: " << node << '\n';
        }
        return;
    }
    

    
}
