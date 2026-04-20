#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

const long long INF = 1e18;
const int W = 8;

// Run Floyd-Warshall on dist matrix in-place, return true if negative cycle found
bool solve(int V, std::vector<std::vector<long long>>& d) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (d[i][k] < INF && d[k][j] < INF && d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];

    for (int i = 0; i < V; i++)
        if (d[i][i] < 0) return true;
    return false;
}

void printMatrix(int V, std::vector<std::vector<long long>>& d) {
    std::cout << std::setw(W) << " ";
    for (int j = 0; j < V; j++)
        std::cout << std::setw(W) << "v" + std::to_string(j);
    std::cout << "\n";

    for (int i = 0; i < V; i++) {
        std::cout << std::setw(W) << "v" + std::to_string(i);
        for (int j = 0; j < V; j++)
            std::cout << std::setw(W) << (d[i][j] >= INF ? "INF" : std::to_string(d[i][j]));
        std::cout << "\n";
    }
}

int main() {
    int V, E;
    std::cout << "Enter V (vertices) and E (edges): ";
    std::cin >> V >> E;

    std::vector<std::vector<long long>> d(V, std::vector<long long>(V, INF));
    for (int i = 0; i < V; i++) d[i][i] = 0;

    std::cout << "Enter each edge as: u v w\n";
    for (int i = 0; i < E; i++) {
        int u, v; long long w;
        std::cin >> u >> v >> w;
        if (w < d[u][v]) d[u][v] = w;
    }

    bool hasCycle = solve(V, d);

    std::cout << "\n--- Floyd-Warshall Distance Matrix ---\n";
    printMatrix(V, d);
    std::cout << "\n";

    if (hasCycle)
        std::cout << "WARNING: Negative cycle detected. Results are unreliable.\n";
    else
        std::cout << "No negative cycle detected.\n";
}