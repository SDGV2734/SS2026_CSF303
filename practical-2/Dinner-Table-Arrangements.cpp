#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cout << "\n========== DINNER TABLE ARRANGEMENT CHECKER ==========" << "\n\n";
    cout << "Enter number of test cases: ";
    cin >> t;
    
    int testCase = 1;
    while(t--) {
        cout << "\n--- Test Case " << testCase++ << " ---\n";
        
        int n;
        cout << "Enter number of friends (1-20): ";
        cin >> n;
        
        // Store allergies as bitmask for each friend
        vector<int> allergy(n, 0);
        
        // Read allergies and convert to bitmask
        for(int i = 0; i < n; i++) {
            int m;
            cout << "\nFriend " << (i + 1) << " - Enter number of allergies: ";
            cin >> m;
            
            cout << "Enter allergy IDs (1-30): ";
            for(int j = 0; j < m; j++) {
                int allergy_id;
                cin >> allergy_id;
                // Set bit for this allergy
                allergy[i] |= (1 << (allergy_id - 1));
            }
        }
        
        // DP using bitmask
        // dp[mask][i] = true if we can arrange people in 'mask' with person 'i' at the end
        cout << "\n Processing...\n";
        vector<vector<bool>> dp(1 << n, vector<bool>(n, false));
        
        // Base case: single person arrangement
        for(int i = 0; i < n; i++) {
            dp[1 << i][i] = true;
        }
        
        // Build up arrangements
        for(int mask = 0; mask < (1 << n); mask++) {
            for(int i = 0; i < n; i++) {
                // If person i is at the end of current arrangement
                if(!dp[mask][i] || !(mask & (1 << i))) {
                    continue;
                }
                
                // Try adding person j next
                for(int j = 0; j < n; j++) {
                    if(mask & (1 << j)) {
                        continue; // j already in arrangement
                    }
                    
                    // Check if i and j can sit adjacent
                    // They can sit adjacent if they don't share any allergy
                    if((allergy[i] & allergy[j]) == 0) {
                        dp[mask | (1 << j)][j] = true;
                    }
                }
            }
        }
        
        // Check if we can arrange all n people
        bool found = false;
        int full_mask = (1 << n) - 1;
        for(int i = 0; i < n; i++) {
            if(dp[full_mask][i]) {
                found = true;
                break;
            }
        }
        
        cout << "\n>>> Result: " << (found ? "✓ YES - Valid arrangement exists!" : "✗ NO - No valid arrangement possible!") << "\n";
    }
    
    cout << "\n========================================================\n";
    cout << "Thank you for using the Dinner Table Arrangement Checker!\n";
    cout << "========================================================\n\n";
    
    return 0;
}
