#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    vector<int> v(n);
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int maxEl = v[0], minEl = v[0], sum = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] > maxEl) maxEl = v[i];
        if (v[i] < minEl) minEl = v[i];
        sum += v[i];
    }

    cout << "Maximum element: " << maxEl << endl;
    cout << "Minimum element: " << minEl << endl;
    cout << "Sum of elements: " << sum << endl;

    return 0;
}