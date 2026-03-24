#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cout << "Enter N (array size) and K (window size): ";
    cin >> n >> k;

    vector<int> a(n);
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) cin >> a[i];

    deque<int> dq;  // stores indices

    cout << "Output: ";
    for (int i = 0; i < n; i++) {
        // Remove indices outside current window
        while (!dq.empty() && dq.front() < i - k + 1)
            dq.pop_front();

        // Remove smaller elements (they can't be max)
        while (!dq.empty() && a[dq.back()] <= a[i])
            dq.pop_back();

        dq.push_back(i);

        // Print max for this window
        if (i >= k - 1)
            cout << a[dq.front()] << " \n"[i == n - 1];
    }
    return 0;
}