#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    priority_queue<int> maxHeap; // max heap for lower half
    priority_queue<int, vector<int>, greater<int>> minHeap; // min heap for upper half

    cout << "Enter " << n << " elements:" << endl;
    cout << fixed << setprecision(1); // format to 1 decimal place

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        // Add to appropriate heap
        if (maxHeap.empty() || x <= maxHeap.top()) {
            maxHeap.push(x);
        } else {
            minHeap.push(x);
        }

        // Balance heaps - maxHeap should have equal or 1 more element
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        // Find and print median
        double median;
        if ((maxHeap.size() + minHeap.size()) % 2 == 1) {
            median = (double)maxHeap.top();
        } else {
            median = ((double)maxHeap.top() + (double)minHeap.top()) / 2.0;
        }

        cout << median << endl;
    }

    return 0;
}
