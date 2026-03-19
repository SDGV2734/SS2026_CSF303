#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, target;
    cout << "Enter the number of elements: ";
    cin >> n;
    
    cout << "Enter the target sum: ";
    cin >> target;

    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // DP table where dp[i][j] = number of subsets with sum j using first i elements
    vector<vector<long long>> dp(n + 1, vector<long long>(target + 1, 0));

    // Base case: one way to make sum 0 (empty subset)
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            // Exclude current element
            dp[i][j] = dp[i - 1][j];

            // Include current element (if possible)
            if (j >= arr[i - 1]) {
                dp[i][j] += dp[i - 1][j - arr[i - 1]];
            }
        }
    }

    cout << "\nNumber of subsets with sum " << target << ": " << dp[n][target] << endl;

    return 0;
}
