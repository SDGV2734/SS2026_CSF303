#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cout << "\n========== MAXIMUM AND SUBARRAY FINDER ==========" << "\n" << endl;
    cout << "Enter number of test cases: ";
    cin >> t;
    
    int testCase = 1;
    while(t--) {
        cout << "\n--- Test Case " << testCase++ << " ---" << endl;
        
        int n, k;
        cout << "Enter N (array size) and K (subarray length): ";
        cin >> n >> k;
        
        vector<int> arr(n);
        cout << "Enter " << n << " integers: ";
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        
        cout << "\n Processing..." << endl;
        
        int maxAnd = 0;
        
        // Check all subarrays of length k
        for(int i = 0; i <= n - k; i++) {
            int currentAnd = arr[i];
            
            // Calculate AND for subarray [i, i+k-1]
            for(int j = i + 1; j < i + k; j++) {
                currentAnd &= arr[j];
            }
            
            maxAnd = max(maxAnd, currentAnd);
        }
        
        cout << "\n>>> Result: Maximum AND value = " << maxAnd << endl;
    }
    
    cout << "\n=" << string(44, '=') << endl;
    cout << "Thank you for using the Maximum AND Subarray Finder!" << endl;
    cout << string(49, '=') << "\n" << endl;
    
    return 0;
}
