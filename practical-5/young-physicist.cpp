#include <iostream>
using namespace std;

int main() {

    // Step 1: Read how many forces
    int n;
    cin >> n;

    // Step 2: Create three counters starting at zero
    // one for each direction X, Y, Z
    int sumX = 0, sumY = 0, sumZ = 0;

    // Step 3: Loop once for each force
    for (int i = 0; i < n; i++) {

        // Read the three values of this force
        int x, y, z;
        cin >> x >> y >> z;

        // Add them to the running totals
        sumX += x;
        sumY += y;
        sumZ += z;
    }

    // Step 4: Check if all three totals are zero
    if (sumX == 0 && sumY == 0 && sumZ == 0)
        cout << "YES" << endl;   // Body is still
    else
        cout << "NO" << endl;    // Body is moving

    return 0;
}