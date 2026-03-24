#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m, k;
    cout << "Enter N (booths), M (coins), K (max skips): ";
    cin >> n >> m >> k;

    vector<int> toll(n);
    cout << "Enter " << n << " toll values: ";
    for (int i = 0; i < n; i++) cin >> toll[i];

    // dp[i][j] = {min_time, max_coins_left} at booth i using j skips so far
    const int INF = 1e9;
    vector<vector<int>> dp(n, vector<int>(k+1, INF));
    vector<vector<int>> coins(n, vector<int>(k+1, 0));
    // from[i][j] = {prev_booth, prev_skips, action}
    vector<vector<tuple<int,int,char>>> from(n, vector<tuple<int,int,char>>(k+1, {-1,-1,' '}));

    dp[0][0] = 0;
    coins[0][0] = m;

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j <= k; j++) {
            if (dp[i][j] == INF) continue;
            int c = coins[i][j];

            // Option 1: pay toll at booth i+1 (cost 1 min)
            if (c >= toll[i+1]) {
                int nt = dp[i][j] + 1, nc = c - toll[i+1];
                if (nt < dp[i+1][j] || (nt == dp[i+1][j] && nc > coins[i+1][j])) {
                    dp[i+1][j] = nt; coins[i+1][j] = nc;
                    from[i+1][j] = {i, j, 'P'};
                }
            }

            // Option 2: skip booth i+1 (cost 2 min, use 1 skip)
            if (j < k) {
                int nt = dp[i][j] + 2;
                if (nt < dp[i+1][j+1] || (nt == dp[i+1][j+1] && c > coins[i+1][j+1])) {
                    dp[i+1][j+1] = nt; coins[i+1][j+1] = c;
                    from[i+1][j+1] = {i, j, 'S'};
                }
            }
        }
    }

    // Find best answer across all skip counts
    int bestTime = INF, bestJ = -1;
    for (int j = 0; j <= k; j++)
        if (dp[n-1][j] < bestTime) { bestTime = dp[n-1][j]; bestJ = j; }

    if (bestTime == INF) { cout << -1; return 0; }

    // Reconstruct path
    cout << "Min time: " << bestTime << "\nPath: ";
    vector<pair<int,char>> path;
    int ci = n-1, cj = bestJ;
    while (ci != 0 || cj != 0) {
        auto [pi, pj, act] = from[ci][cj];
        path.push_back({ci+1, act});
        ci = pi; cj = pj;
    }
    path.push_back({1, 'S'});
    reverse(path.begin(), path.end());
    for (auto [booth, act] : path)
        cout << booth << (act=='P'?" [pay] ":" [skip] ");
    cout << "\n";
    return 0;
}