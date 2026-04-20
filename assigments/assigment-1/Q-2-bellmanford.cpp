#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

// Edge representation
struct Edge {
    int u, v, w;
};

constexpr long long INF = std::numeric_limits<long long>::max() / 2;

/**
 * Bellman-Ford Algorithm
 *
 * Complexity: O(V * E) time, O(V) space
 *
 * @param V      number of vertices (0-indexed)
 * @param edges  list of directed weighted edges
 * @param src    source vertex
 * @return       pair<dist[], has_negative_cycle>
 */
std::pair<std::vector<long long>, bool>
bellman_ford(int V, const std::vector<Edge>& edges, int src) {

    std::vector<long long> dist(V, INF);
    dist[src] = 0;

    // Relax all edges (V-1) times
    for (int iter = 0; iter < V - 1; ++iter) {
        bool updated = false;
        for (const Edge& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
            }
        }
        // Early termination: no update means shortest paths are settled
        if (!updated) break;
    }

    // V-th relaxation pass: detect negative-weight cycle
    bool neg_cycle = false;
    for (const Edge& e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
            neg_cycle = true;
            break;
        }
    }

    return {dist, neg_cycle};
}

int main() {
    int V, E;
    std::cout << "Enter V (vertices) and E (edges): ";
    std::cin >> V >> E;

    std::vector<Edge> edges(E);
    std::cout << "Enter each edge as: u v w\n";
    for (Edge& e : edges) std::cin >> e.u >> e.v >> e.w;

    int src;
    std::cout << "Enter source vertex: ";
    std::cin >> src;

    auto [dist, has_neg_cycle] = bellman_ford(V, edges, src);

    std::cout << "\n--- Bellman-Ford Results (source = " << src << ") ---\n";

    if (has_neg_cycle) {
        std::cout << "WARNING: Negative-weight cycle detected!\n"
                  << "Shortest paths are undefined for affected vertices.\n";
    } else {
        std::cout << "No negative-weight cycle detected.\n";
    }

    std::cout << "\nVertex  Distance from source\n";
    std::cout << "------  --------------------\n";
    for (int v = 0; v < V; ++v) {
        std::cout << std::setw(6) << v << "  ";
        if (dist[v] == INF)
            std::cout << "UNREACHABLE\n";
        else
            std::cout << dist[v] << "\n";
    }

    return 0;
}