#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;

int main() {
    vector<int> v20240101;
    int input;

    
    cout << "Enter 6 values: ";
    for (int i = 0; i < 6; i++) {
        cin >> input;
        v20240101.push_back(input);
    }

    
    cout << "\nOriginal : ";
    for (int val : v20240101) cout << val << " ";
    cout << endl;

    sort(v20240101.begin(), v20240101.end());
    cout << "Sorted   : ";
    for (int val : v20240101) cout << val << " ";
    cout << endl;


    int minVal = *min_element(v20240101.begin(), v20240101.end());
    int maxVal = *max_element(v20240101.begin(), v20240101.end());
    int sumVal =  accumulate(v20240101.begin(), v20240101.end(), 0);
    double average = (double)sumVal / v20240101.size();

    cout << "\nMin     : " << minVal << endl;
    cout << "Max     : " << maxVal << endl;
    cout << "\nSum     : " << sumVal << endl;
    cout << "\nAverage : " << fixed << setprecision(2) << average << endl;


    v20240101.erase(
        remove_if(v20240101.begin(), v20240101.end(),
            [average](int val) { return val < average; }),
        v20240101.end()
    );

    cout << "\nAfter removing below average:" << endl;
    for (int val : v20240101) cout << val << " ";
    cout << endl;

    return 0;
}