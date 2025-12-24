/** A Connected Component of an UNDIRECTED graph is a 
 * maximal set of vertices in which there is always a 
 * path between any pair of vertices.
 */

/* Given a graph with isolated "Connected Components"
 * - Imagine a map with Islands and large continents.
 * To count the number of connected components, we 
 * can use the classic BFS algorithm since the order
 * of vertices does NOT matter. When a vertice has 
 * NOT been discovered in the array of adjacency Vertices
 * We increment the "Count of Connected Components"! 
 * and do a BFS on that vertice!
 * This is because if the whole graph is connected
 * Then a BFS on any single vertex as ROOT (remember undirected graph)
 * will allow us to discover all the other vertices which 
 * will all have some path to it (Remember BFS algorithm!).
 * 
 * But if vertex A and B have no path between them,
 * A BFS with vertex A as root will NEVER discover B 
 * and mutually the same with a BFS on vertex B as ROOT!
 * This is where directed vs undirected matters!
 * Imagine in a directed graph, if there is a directed path from 
 * B -> A, a BFS with A as ROOT first will still never lead to B!
 * And A and B will be counted as separate "connected components"
 */


#include "graph.h"
void connected_components(Graph& G) {
    int components = 0;
    
    for ()
}
