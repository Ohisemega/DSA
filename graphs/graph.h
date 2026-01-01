#include <iostream>
#include <array>
#define MAX 200

enum class NodeState{
    UNDISCOVERED,
    DISCOVERED,
    PROCESSED
};

enum class EdgeClass{
    BACK_EDGE  = 0,
    TREE_EDGE  = 1,
    FWD_EDGE   = 2,
    CROSS_EDGE = 4,
    NO_EDGE    = 8,
};
// An Adjacency Graph Implementation!
typedef struct edgeNode{
    int y;  // ID of this NODE!!!
    int weight; // Weight of this edge if any
    EdgeClass eclass; // classification of the edge parent ----> y;
    struct edgeNode* next;
}edgeNode;

typedef struct Graph{
    Graph(bool directed, unsigned int maxV, unsigned int maxE): directed{directed}, nvertices{1}, nedges{0} {
        
    }
    void initialize() {
        for (int i = 1; i < MAX; ++i) {
            this->degree[i] = 0;
            this->adjacentNodesListArray[i] = NULL;
        }
        states.fill(NodeState::UNDISCOVERED);
        parents.fill(-1);
    }
    void read_graph() {
        int edgeCount;
        int x, y, W;

        std::cout << "Enter the number of Edges: ";
        std::cin >> edgeCount;
        std::cout << "Enter the number of Vertices: ";
        std::cin >> nvertices;
        ++nvertices;
        std::cout << '\n';
        for (int i = 0; i < edgeCount; ++i) {
            std::cin >> x;
            std::cout << ' ';
            std::cin >> y;
            std::cout << ' ';
            std::cin >> W;
            std::cout << '\n';
            this->insert_edge(x, y, W);
            ++this->degree[x];
            ++this->nedges;
            if(!directed){
                ++degree[y];
                this->insert_edge(y, x, W);
            }
        }
        std::cout << "The no. of edges is: " << this->nedges << '\n';
    }
    std::array<edgeNode*, MAX+1>& getList() {
        return adjacentNodesListArray;
    }

    int vertices() const {
        return nvertices;
    }

    int edges() const{
        return nedges;
    }

    bool is_directed() const{
        return directed;
    }

    void public_insert(int x, int y, int weight = 0){
        ++this->degree[x];
        ++this->nedges;
        ++this->nedges;
        if(!directed){
            ++degree[y];
            this->insert_edge(y, x, weight);
        }
        insert_edge(x, y, weight);
    }

    std::array<NodeState, MAX+1> states;
    std::array<int, MAX+1> parents;
    private:
        bool directed; // Is the graph directed or undirected. This will influence how we add edges (reciprocal/nor reciprocal: x-y: x has an edge to y, does y have an edge to x??)
        int nedges; // current number of vertices currently in the graph
        int nvertices; // current number of vertices currently in the graph
        std::array<edgeNode*, MAX+1> adjacentNodesListArray;
        std::array<int, MAX+1> degree; // The number of adjacent nodes for each node
        void insert_edge(int x, int y, int weight){
            edgeNode *p = nullptr;
            p = new edgeNode{y, weight, EdgeClass::NO_EDGE, adjacentNodesListArray[x]};
            adjacentNodesListArray[x] = p;
        }
} Graph;

// The  nvertices and
//      nedges count are actually statistical metrics fir an object of this class/struct.
// They are good for fast query but not utilized directly by algorithms working on this DS

