#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int totalSubsets = 1 << n; // 2^n subsets
    int evenCount = 0;

    for (int mask = 0; mask < totalSubsets; mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            // Check if i-th bit is set in mask
            if (mask & (1 << i)) {
                sum += arr[i];
            }
        }
        // Check if sum is even
        if (sum % 2 == 0) {
            evenCount++;
        }
    }

    cout << "\nNumber of subsets with even sum: " << evenCount << endl;

    return 0;
}
