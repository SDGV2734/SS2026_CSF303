#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<long long,int> pli;

int main(){
    int n, m;
    cout << "Enter N (routers) and M (cables): "; cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n+1);
    cout << "Enter M edges (u v w):\n";
    for(int i = 0; i < m; i++){
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<long long> dist(n+1, LLONG_MAX);
    vector<int> prev(n+1, -1);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[1] = 0; pq.push({0, 1});

    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        for(auto [v, w] : adj[u])
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
    }

    if(dist[n] == LLONG_MAX){ cout << -1; return 0; }
    cout << "Min latency: " << dist[n] << "\nPath: ";
    vector<int> path; int cur = n;
    while(cur != -1){ path.push_back(cur); cur = prev[cur]; }
    reverse(path.begin(), path.end());
    for(int i = 0; i < path.size(); i++)
        cout << path[i] << (i+1<path.size() ? " -> " : "\n");
}