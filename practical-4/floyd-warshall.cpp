#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = 1e9;

void floydWarshall(vector<vector<int>>& dist) {
    int n = dist.size();

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j],
                                     dist[i][k] + dist[k][j]);
}

void printMatrix(const vector<vector<int>>& dist,
                 const vector<char>& nodes) {
    int n = nodes.size();
    
    // Print header row
    cout << "\n+-------";
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
}

int main() {
    vector<char> nodes = {'A','B','C','D'};
    int I = INF;
    vector<vector<int>> dist = {
        {0, 3, I, 7},
        {8, 0, 2, I},
        {5, I, 0, 1},
        {2, I, I, 0}
    };

    floydWarshall(dist);

    cout << "Shortest distance matrix:\n";
    printMatrix(dist, nodes);
    return 0;
}