#include<iostream>
#include<cmath>
using namespace std;

int main() {
    long long ab, bc, ac;
    cin >> ab >> bc >> ac;
    
    // ab = a*b, bc = b*c, ac = a*c
    // a*b * a*c / b*c = a^2  =>  a = sqrt(ab*ac/bc)
    long long a = round(sqrt((double)ab * ac / bc));
    long long b = ab / a;
    long long c = bc / b;
    
    cout << 4 * (a + b + c) << endl;
}