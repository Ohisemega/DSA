#include <iostream>
#include <tuple>
#include <array>
#include <limits>
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
    EdgeClass eclass; // classification of the edge "adj_list[x]---->y";
    struct edgeNode* next;
}edgeNode;

struct Adjacency_Matrix {
    std::array<int, MAX+1> parents;
    std::array<NodeState, MAX+1> states;
   
    void initialize(){
        for(int i = 0; i < MAX+1; ++i){
            weights[i].fill(std::numeric_limits<int>::max()); // each edge has an infinite cost to access the end-node
        }
        parents.fill(-1);
        states.fill(NodeState::UNDISCOVERED);
        degree.fill(0); // each node initialized to having no neighbour
        weighted = directed = false; // initialized as not weighted nor directed
        nvertices = nedges = 0; // no edges in the graph initially
    }

    bool is_directed() const{
        return directed;
    }

    bool is_weighted() const{
        return weighted;
    }

    int edges() const{
        return nedges;
    }

    int vertices() const{
        return nvertices;
    }

    void read_graph(){
        int edgeCount;
        int x, y, W;
        std::cout << "Enter the number of Edges: ";
        std::cin >> edgeCount;
        std::cout << "Enter the number of Vertices: ";
        std::cin >> nvertices;
        std::cout << "Is the graph weighted or unweighted (1 or 0): ";
        std::cin >> weighted;
        std::cout << "Is the graph directed or undirected (1 or 0): ";
        std::cin >> this->directed;

        for (int i = 0; i < edgeCount; ++i) {
            W = 0;
            std::cin >> x;
            std::cout << ' ';
            std::cin >> y;
            if(x < 0 || x > MAX || y < 0 || y > MAX){
                std::cout << "Warning: Try again, and enter a positive number between 0 and " << MAX << '\n';
                continue;
            }else{
                if(this->weighted) {
                    std::cout << ' ';
                    std::cin >> weights[x][y];
                    ++degree[x];
                    if(!directed){
                        weights[y][x] = weights[x][y];
                        ++degree[y];
                    }
                    std::cout << '\n';
                }else{
                    weights[x][y] = 1;
                    ++degree[x];
                    if(!directed){
                        weights[y][x] = 1;
                        ++degree[y];
                    }
                }
                ++this->degree[x];
                ++this->nedges;
            }
        }
    }

    private:
        std::array<int, MAX+1> degree; // number of neighbours each vertex has
        std::array<std::array<int, MAX+1>, MAX+1> weights; /* adjacency/weight info */
        int nedges;
        int nvertices;
        bool directed;
        bool weighted; // edge weighted
};

typedef struct Graph{
    Graph(bool directed_, bool weighted_, unsigned int maxV, unsigned int maxE): directed{directed_}, weighted{weighted_},  nvertices{1}, nedges{0} {
        
    }
    void initialize() {
        adjacentNodesListArray.fill(nullptr);
        degree.fill(0);
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
        std::cout << "Is the graph weighted or unweighted (1 or 0): ";
        std::cin >> this->weighted;
        std::cout << "Is the graph directed or undirected (1 or 0): ";
        std::cin >> this->directed;
        
        std::cout << '\n';
        for (int i = 0; i < edgeCount; ++i) {
            W = 0;
            std::cin >> x;
            std::cout << ' ';
            std::cin >> y;
            if(this->weighted) {
                std::cout << ' ';
                std::cin >> W;
                std::cout << '\n';
            }
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

    unsigned int vertices() const {
        return nvertices;
    }

    unsigned int edges() const{
        return nedges;
    }

    bool is_directed() const{
        return directed;
    }

    bool is_weighted() const{
        return weighted;
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
        bool weighted;
        bool directed; // Is the graph directed or undirected. This will influence how we add edges (reciprocal/nor reciprocal: x-y: x has an edge to y, does y have an edge to x??)
        unsigned int nedges; // current number of vertices currently in the graph
        unsigned int nvertices; // current number of vertices currently in the graph
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

/** Implementation for a Union_Find Data Structure! This will support the Kruskal Algorithm for finding the MST **/
struct UnionFind{
    std::array<int, MAX+1> parents;
    std::array<int, MAX+1> sz; // Size of elements in the subtree
    void initialize() {
        for(int i = 0; i < parents.size(); ++i) {
            parents[i] = i; // every node is initially it's own parent
        }
        sz.fill(1);
        N = 0;
    }

    std::tuple<bool, int, int> is_same_tree(int n1, int n2) {
        int i, j;
        for(i = n1; i != parents[i]; i = parents[i]);
        for(j = n2; j != parents[j]; j = parents[j]);
        return std::tuple(i == j, i, j);
    }

    void union_alg(int i, int j){
        if(sz[i] < sz[j]){
            parents[i] = j;
            sz[j] += sz[i];
            N = std::max(N, sz[j]);
        }else{
            parents[j] = i;
            sz[i] += sz[j];
            N = std::max(N, sz[j]);
        }
    }
    
    int getMaxTreeSize() const{
        return N;
    }

    private:
        int N; // maximum number of vertices in any tree in this forest!
};

