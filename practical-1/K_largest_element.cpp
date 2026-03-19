#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, k;
    cout << "Enter N and K: ";
    cin >> n >> k;

    if (k <= 0 || k > n) {
        cout << "Invalid K value!" << endl;
        return 0;
    }

    priority_queue<int> pq; // max heap by default
    
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pq.push(x);
    }

    cout << "\n" << k << " largest elements: ";
    for (int i = 0; i < k; i++) {
        if (i > 0) cout << " ";
        cout << pq.top();
        pq.pop();
    }
    cout << endl;

    return 0;
}