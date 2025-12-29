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
 *  We use two STACKs to simulate delayed computation,
 *  The 1st stack was for simulating the recursive call to new nodes model
 *  The 2nd stack was recording the access mode of nodes bottom to top
 *  And we run a seperate while loop to Unwind the calls to each accessed node
 *  marking them as PROCESSED!
 *  But in using a stack, we push the first UNDISCOVERED
 *  node to the bottom of the stack. To mimic the Recursion
 *  model, we actually want to visit the node at the bottom
 *  of the STACK!
 *  In my implementation, I used a vector first to store all UNDISCOVERED
 *  VERTICES, then pushed them in the reverse order (end-to-beginning)
 *  into a STACK DS. So we have the first DISCOVERD at the top of the 
 *  STACK! 
 */
#include "graph.h"
#include <stack>
#include <vector>

void process_edge(Graph& G, int parent, int child);
void process_node_early(Graph& G, int node);
void process_node_late(Graph& G, int node);
bool process_edge_cycle_search(int start, int end, std::array<int, MAX+1>& parents);

std::array<int, MAX+1> entry_time;
std::array<int, MAX+1> exit_time;
std::array<int, MAX+1> reachable_ancestor;
std::array<int, MAX+1> tree_node_degree; /*This is an array that stores the number of TREE-EDGES each node in a GRAPH has during a DFS-Traversal-Tree generation from some arbitrary root!*/
static int time_cnt = 0;
std::vector<int> articulation_vertices;

void DFS_module_init(){
    entry_time.fill(-1);
    exit_time.fill(-1);
    reachable_ancestor.fill(-1);
    tree_node_degree.fill(0);
    articulation_vertices.clear();
}

/** If We want to Run an algorithm which iteratively removes each node piece from this graph and tests for connected components
 * We can achieve this by setting the linked-list index in the adjacency array of vertices to 0. That way When the DFS algorithm tries to DFS to
 * that node, it meets a nullptr entry! Assuming the GRAPH was originally FULLY-CONNECTED-COMPONENT.
 * for(int i = 1; i < G.vertices(); ++i) {
 *      edgeNode* cache = G.getList()[i];
 *      G.getList()[i] = nullptr;
 *      if(i == 1) DFS_traversal(G, i++, is_cycle)
 *      else DFS_traversal(G, 1, is_cycle);
 *      G.getList()[i] = cache;
 *      for(i = 1; i < G.vertices(); i++) {
 *          if(G.states[i] == NodeState::UNDISCOVERED){
 *              std::cout << i << " is an ARTICULATION vertex!\n";
 *              break;
 *          }
 *      }
 *
 * }
 */
void DFS_traversal(Graph& G, int Root, bool& is_cycle ){
    std::stack<int> stk;
    std::stack<int> unwind;
    std::vector<int> vec;
    vec.reserve(64);
    stk.push(Root);
    edgeNode* itr = nullptr;
    G.states[Root] = NodeState::DISCOVERED;
    is_cycle = false;
    while(!stk.empty()) {
        time_cnt++;
        int top = stk.top();
        unwind.push(top); // This STACK DS tracks the access mode of all nodes accessed from the DFS-traversal root to all leaves, and at the end of this while loop, we unpack this stack too!
        stk.pop();
        if(G.states[top] == NodeState::PROCESSED) continue; // If the node state is processed, skip everything!
        entry_time[top] = time_cnt;
        
        process_node_early(G, top);
        for(itr = G.getList()[top]; itr != nullptr; itr = itr->next) {
            if(G.states[itr->y] == NodeState::UNDISCOVERED){
                G.states[itr->y] = NodeState::DISCOVERED;
                G.parents[itr->y] = top; // TREE-EDGE
                vec.push_back(itr->y);
                process_edge(G, top, itr->y); // do we want to process the edge early?!!
            }else if((G.states[itr->y] == NodeState::DISCOVERED && G.parents[itr->y] != top/*BACK-EDGE*/) || G.is_directed()) {
                // We check for the condition of G.is_directed() because in a directed graph, each edge (NOT NODE) has one discovery chance!
                // In a directed graph, top ----> itr->y is still a BACK_EDGE, but we will have no access to that EDGE if we ignore THIS case!
                // If an edge leads from Node-top to a DISCOVERED node itr->y, it must be processed now or LOST!
                // In an undirected graph, that is simply a BACK_EDGE and useful for identifying cycles or updating reachable_ancestor[] IDs 
                if(G.states[itr->y] == NodeState::DISCOVERED && G.parents[top] != itr->y) is_cycle = true; // This Graph HAS A CYCLE!
                process_edge(G, top, itr->y);
            }
        }
        for(int i = vec.size()-1; i >= 0; --i) {
            stk.push(vec[i]);
        }
        vec.clear();
    }
    
    // This step simulates unwinding the recursive call of the DFS-traversal once we have 
    // traversed the whole connected component of Root. We recorded the access mode in reverse 
    // in the unwind STACK and simply popped it here while processing the nodes, and adding 
    // exit time-stamps!
    while(!unwind.empty()){
        int unwind_node = unwind.top();
        unwind.pop();
        process_node_late(G, unwind_node);
        time_cnt++;
        exit_time[unwind_node] = time_cnt;
        G.states[unwind_node] = NodeState::PROCESSED;
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
            process_edge(G, Root, itr->y);
            DFS_traversal_rec(G, Root, is_cycle); // The Recursive DFS_traversal_rec() call!
        }else if((G.states[itr->y] != NodeState::PROCESSED && G.parents[Root] != itr->y) || (G.is_directed())){
            is_cycle = process_edge_cycle_search(Root, itr->y, G.parents);
            process_edge(G, Root, itr->y);
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

/** process_nodde_early simply sets the reachable_ancestor
 * of any node o be itself!
 */
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
 * if TREE_EDGE: Increment the tree_node_degree entry for the DFS-Traversal tree of the GRAPH
 * if EDGE_NODE: Check if y is x's parent, if not, check the earliest ancestor of x! and update the ancestor if y is earlier than x's current earliest ancestor
 *               Do this by checking entry_time[y] is < entry_time[reachable_ancestor[x]]; if so, update reachable_ancestor[x] = y;
 */
void process_edge(Graph& G, int parent, int child) {
    EdgeClass eclass = edge_classification(parent, child);

    if(eclass == EdgeClass::TREE_EDGE) {
        ++tree_node_degree[parent]; // The Tree Edge from the Parent--to-->Child. Here, the Child was in an UNDISCOVERED state, and the Parent is it's direct ancestor automatically!
        // Hence, the parent has a TREE_EDGE going out to the child in the DFS-Traversal and that is one more node_degree for the parent!
    }

    if(eclass == EdgeClass::BACK_EDGE && (G.parents[parent] != child)) {
        // Remember that the child is the parent's ancestor in this case
        // The reachable ancestor is first update when we process_edge(parent, child) and the edge is a BACK_EDGE!
        if(entry_time[child] < entry_time[reachable_ancestor[parent]]) { // If the entry_time[child] is earlier than the entry_time[parent's current reachable ancestor]:
                                                                         // Then we update the parent's reachable ancestor as we have an older one in view now!
            reachable_ancestor[parent] = child;
        }
    }
}

/** This algorithm is run when a DFS is unwinding the call stack that is associated with a node in the recursive version
 * In the iterative version, it is called when the first while-loop has completed!
 * We run another while-loop over an unwind STACK to simulate the recursive ature of popping call frames off the Program stack!
 *
 * For every node which process_node_late runs on, it's child-node (if any) has updated it's reachable_ancestor[node]
 * This is the last statement of every process_node_late(...) method - which the child runs on unwinding it's stack (occurs before 
 *  parent node's call stack unwinds)!
 */
void process_node_late(Graph& G, int node) {
    bool root;
    int time_node;
    int time_parent;
    
    // the parent of the ROOT node of DFS/BFS-Tree traversal is always -1! This will particularly hold once the node has been FULLY PROCESSED!
    // All other nodes in the DFS/BFS-traversal Tre will have another node as a parent asides from the initial given node to iterate from!
    if(G.parents[node] == -1 && tree_node_degree[node] > 1) { // If the node is the DFS-Traversal tree ROOT, then we check how many TREE-EDGES it has when we process process_edge(ROOT, SomeChild)...
        // If the ROOT node of a DFS-traversal has more than 1 TREE-EDGE, then it is a Root Articulation!
        std::cout << "Root articulation vertex: " << node << '\n';
        return;
    }
    
    root = G.parents[G.parents[node]] == -1; // Remember (G.parents[NODE_ID] == -1) ===> means NODE_ID is the ROOT.
                                             // Here we are checking if The parent of the node - G.parents[node] is the ROOT_NODE itself
                                             // i.e. if the parent of the parent of node is the ROOT_NODE itself!
    if(!root) {
        if(reachable_ancestor[node] == G.parents[node]) { // This is possible if it's child node in the DFS-Traversal tree update it's reachable ancestor to be this node's parent!
                                                          // Imagine a section of the DFS-Traversal tree's path is: A ---> B ---> C 
                                                          //                                                        |____<________|
                                                          // With a BACK_EDGE from C to A, so C will unwind and update B's reachable_ancestor[B] == A!
            std::cout << "Parent Articulation Vertex! " << G.parents[node] << '\n';
            articulation_vertices.push_back(G.parents[node]);
        }else if(reachable_ancestor[node] == node) {
            std::cout << "Bridge Articulation Vertex: " << node << '\n';
            articulation_vertices.push_back(G.parents[node]);

            if(tree_node_degree[node] > 0) { // If node is NOT a LEAF_NODE i.e. it has tree_node_degree[node] > 0 (at least one child in the DFS-traversal tree)
                std::cout << "Bridge Articulation Vertex: " << node << '\n';
                articulation_vertices.push_back(node);
            }
        }
    }      
    time_node = entry_time[reachable_ancestor[node]];
    time_parent = entry_time[reachable_ancestor[G.parents[node]]];

    if(time_node < time_parent) { // Update node's parent's reachable ancestor if node has one more ancient than parent's!
                                  // Remember that DFS-traversal will next call this function on node's parent!
        reachable_ancestor[G.parents[node]] = reachable_ancestor[node];
    }
}
