#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    int n, k;
    cout << "Enter N and K: ";
    if (!(cin >> n >> k)) return 0;

    if (n <= 0) {
        cout << "No elements to process." << endl;
        return 0;
    }

    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) cin >> arr[i];

    if (k <= 0 || k > n) {
        cout << "Invalid window size" << endl;
        return 0;
    }

    deque<int> dq; // storing indices for useful elements

    cout << "\nWindow maxima: ";
    for (int i = 0; i < n; ++i) {
        // remove indices out of current window
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();

        // remove smaller values at back
        while (!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();

        dq.push_back(i);

        // window has formed, output its max
        if (i >= k - 1) {
            if (i > k - 1) cout << " ";
            cout << arr[dq.front()];
        }
    }
    cout << endl;

    return 0;
}
