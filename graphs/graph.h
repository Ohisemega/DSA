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
    CROSS_EDGE = 4
};
// An Adjacency Graph Implementation!
typedef struct edgeNode{
    int y;  // ID of this NODE!!!
    int weight; // Weight of this edge if any
    struct edgeNode* next;
}edgeNode;

typedef struct Graph{
    Graph(bool directed, unsigned int maxV, unsigned int maxE): directed{directed}, nvertices{0}, nedges{0} {
        
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
        int x, y;

        std::cout << "Enter the number of Edges: ";
        std::cin >> edgeCount;
        std::cout << "Enter the number of Vertices: ";
        std::cin >> nvertices;
        std::cout << '\n';
        for (int i = 0; i < edgeCount; ++i) {
            std::cin >> x;
            std::cout << ' ';
            std::cin >> y; 
            std::cout << '\n';
            this->insert_edge(x, y);
            ++this->degree[x];
            ++this->nedges;
            if(!directed){
                ++degree[y];
                this->insert_edge(y, x);
            }
        }
        std::cout << "The no. of edges is: " << this->nedges << '\n';
    }
    std::array<edgeNode*, MAX+1> getList() const{
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

    std::array<NodeState, MAX+1> states;
    std::array<int, MAX+1> parents;
    private:
        bool directed; // Is the graph directed or undirected. This will influence how we add edges (reciprocal/nor reciprocal: x-y: x has an edge to y, does y have an edge to x??)
        int nedges; // current number of vertices currently in the graph
        int nvertices; // current number of vertices currently in the graph
        std::array<edgeNode*, MAX+1> adjacentNodesListArray;
        int degree[MAX+1]; // The number of adjacent nodes for each node
        void insert_edge(int x, int y){
            edgeNode *p = nullptr;
            p = new edgeNode{y, 0, adjacentNodesListArray[x]};
            adjacentNodesListArray[x] = p;
        }
} Graph;

// The  nvertices and
//      nedges count are actually statistical metrics fir an object of this class/struct.
// They are good for fast query but not utilized directly by algorithms working on this DS

