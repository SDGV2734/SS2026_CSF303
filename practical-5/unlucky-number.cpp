#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    int n;
    string s;

    cin >> n;
    cin >> s;

    string first = s.substr(0, n);
    string second = s.substr(n, n);

    sort(first.begin(), first.end());
    sort(second.begin(), second.end());

    bool less = true, greater = true;

    for(int i = 0; i < n; i++) {
        if(first[i] >= second[i])
            less = false;

        if(first[i] <= second[i])
            greater = false;
    }

    if(less || greater)
        cout << "YES";
    else
        cout << "NO";

    return 0;
}