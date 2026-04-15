#include<iostream>
#include<set>
using namespace std;

bool distinctDigits(int n) {
    set<int> digits;
    while (n > 0) {
        int d = n % 10;
        if (digits.count(d)) return false;
        digits.insert(d);
        n /= 10;
    }
    return true;
}

int main() {
    int y;
    cin >> y;
    y++;
    while (!distinctDigits(y)) y++;
    cout << y << endl;
}