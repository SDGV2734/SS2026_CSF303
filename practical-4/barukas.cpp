#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge { int u, v, w; };

// ── Union-Find ────────────────────────────────────────
struct UnionFind {
    vector<int> parent, rank_;
    UnionFind(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }
};

// ── Borůvka's Algorithm ───────────────────────────────
pair<vector<Edge>, int> boruvka(int n, vector<Edge>& edges) {
    UnionFind uf(n);
    vector<Edge> mst;
    int totalWt   = 0;
    int components = n;

    while (components > 1) {
        // cheapest[comp] = index of cheapest outgoing edge
        vector<int> cheapest(n, -1);

        for (int i = 0; i < (int)edges.size(); i++) {
            int cu = uf.find(edges[i].u);
            int cv = uf.find(edges[i].v);
            if (cu == cv) continue;

            if (cheapest[cu] == -1 || edges[i].w < edges[cheapest[cu]].w)
                cheapest[cu] = i;
            if (cheapest[cv] == -1 || edges[i].w < edges[cheapest[cv]].w)
                cheapest[cv] = i;
        }

        for (int comp = 0; comp < n; comp++) {
            if (cheapest[comp] == -1) continue;
            Edge& e = edges[cheapest[comp]];
            if (uf.unite(e.u, e.v)) {
                mst.push_back(e);
                totalWt += e.w;
                components--;
            }
        }
    }
    return {mst, totalWt};
}

int main() {
    string nodes[] = {"A","B","C","D","E","F"};
    int n = 6;
    vector<Edge> edges = {
        {0,1,4},{0,2,3},{1,2,1},{1,3,2},
        {2,3,4},{3,4,2},{4,5,6},{3,5,5}
    };

    auto [mst, weight] = boruvka(n, edges);

    cout << "MST edges:\n";
    for (auto& e : mst)
        cout << "  " << nodes[e.u] << " -- " << nodes[e.v]
             << "  (weight " << e.w << ")\n";
    cout << "Total MST weight: " << weight << "\n";
    return 0;
}