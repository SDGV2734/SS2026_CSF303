#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = 1e9;

struct Edge { int u, v, w; };

// ── Bellman-Ford from virtual node ───────────────────
vector<int> bellmanFord(int n, vector<Edge>& edges) {
    // n+1 nodes: 0..n-1 original, n = virtual node q
    vector<int> h(n + 1, INF);
    h[n] = 0;
    for (int i = 0; i < n; i++) {
        // Relax original edges
        for (auto& e : edges)
            if (h[e.u] != INF && h[e.u] + e.w < h[e.v])
                h[e.v] = h[e.u] + e.w;
        // Virtual node q connects to all with w=0
        for (int v = 0; v < n; v++)
            if (h[n] + 0 < h[v])
                h[v] = 0;
    }
    // Negative cycle detection
    for (auto& e : edges)
        if (h[e.u] != INF && h[e.u] + e.w < h[e.v])
            throw runtime_error("Negative cycle detected");
    return h;
}

// ── Dijkstra (min-heap) ───────────────────────────────
vector<int> dijkstra(int n, vector<vector<pair<int,int>>>& adj, int src) {
    vector<int> dist(n, INF);
    dist[src] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u])
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
    }
    return dist;
}

// ── Johnson's Algorithm ───────────────────────────────
vector<vector<int>> johnsons(int n, vector<Edge>& edges) {
    // Step 1 & 2: get potentials via Bellman-Ford
    vector<int> h = bellmanFord(n, edges);

    // Step 3: reweight
    vector<vector<pair<int,int>>> adj(n);
    for (auto& e : edges)
        adj[e.u].push_back({e.v, e.w + h[e.u] - h[e.v]});

    // Step 4 & 5: Dijkstra + restore
    vector<vector<int>> result(n, vector<int>(n, INF));
    for (int u = 0; u < n; u++) {
        auto d = dijkstra(n, adj, u);
        for (int v = 0; v < n; v++)
            if (d[v] != INF)
                result[u][v] = d[v] + h[v] - h[u];
    }
    return result;
}

int main() {
    char nodes[] = {'A','B','C','D'};
    int n = 4;
    vector<Edge> edges = {
        {0,1,3},{0,3,7},{1,0,8},{1,2,2},
        {2,0,5},{2,3,1},{3,0,2}
    };

    auto dist = johnsons(n, edges);
    
    cout << "\nAll-pairs shortest distances:\n";
    
    // Print header row
    cout << "+-------";
    for (int i = 0; i < n; i++) cout << "-------+";
    cout << "\n|  To   |";
    for (char c : nodes) cout << "  " << c << "   |";
    cout << "\n+-------";
    for (int i = 0; i < n; i++) cout << "-------+";
    cout << "\n";
    
    // Print each row
    for (int i = 0; i < n; i++) {
        cout << "| From " << nodes[i] << " |";
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) cout << " INF |";
            else {
                if (dist[i][j] < 10) cout << "  " << dist[i][j] << "  |";
                else cout << "  " << dist[i][j] << " |";
            }
        }
        cout << "\n";
    }
    
    // Print bottom border
    cout << "+-------";
    for (int i = 0; i < n; i++) cout << "-------+";
    cout << "\n";
    
    return 0;
}