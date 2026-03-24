#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;
typedef pair<double,int> pdi;

int main(){
    int n, m;
    cout << "Enter N and M: "; cin >> n >> m;

    // adj[u] = {v, a, b} where travel time = a*t + b
    vector<vector<tuple<int,double,double>>> adj(n+1);
    cout << "Enter M directed edges (u v a b):\n";
    for(int i = 0; i < m; i++){
        int u, v; double a, b; cin >> u >> v >> a >> b;
        adj[u].push_back({v, a, b});
    }

    vector<double> dist(n+1, 1e18);
    vector<int> prev(n+1, -1);
    priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
    dist[1] = 0; pq.push({0.0, 1});

    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        for(auto [v, a, b] : adj[u]){
            double arr = d + a*d + b;   // arrive at v at time d + f(d)
            if(arr < dist[v]){
                dist[v] = arr; prev[v] = u;
                pq.push({arr, v});
            }
        }
    }

    if(dist[n] >= 1e17){ cout << -1; return 0; }
    cout << fixed << setprecision(2) << dist[n] << "\n";
}