#include <iostream>
#include <vector>
#include <algorithm>
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

	sort(arr.begin(), arr.end());

	cout << "\nUnique elements: ";
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (i == 0 || arr[i] != arr[i - 1]) {
			if (count > 0) {
				cout << " ";
			}
			cout << arr[i];
			count++;
		}
	}
	cout << endl;

	return 0;
}
