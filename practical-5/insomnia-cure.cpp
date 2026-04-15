#include <iostream>  // Include the input/output stream library
using namespace std;

int main() {
    // Declare variables to store input values
    int k, l, m, n, d;

    // Read values for k, l, m, n, and d from the user
    cin >> k >> l >> m >> n >> d;

    int count = 0;  // Initialize a counter to keep track of damaged dragons

    // Loop through each dragon numbered from 1 to d
    for (int i = 1; i <= d; i++) {
        // Check if the current dragon is damaged by any of the hazards
        // If i is divisible by k, l, m, or n, it is damaged
        if (i % k == 0 || i % l == 0 || i % m == 0 || i % n == 0) {
            count++;  // Increment the counter if the dragon is damaged
        }
    }

    // Output the total number of damaged dragons
    cout << count << endl;

    return 0;  // Indicate that the program finished successfully
}