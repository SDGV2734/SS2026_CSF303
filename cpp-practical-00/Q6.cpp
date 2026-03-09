#include <iostream>
#include <string>
using namespace std;

int main() {
    string firstName = "sonam";
    string fullName = "sonam dorji";
    string studentNumber = "02230299";

    
    int firstNameLen = firstName.length();
    cout << "Name repeated (" << firstNameLen << " times):" << endl;
    for (int i = 0; i < firstNameLen; i++) {
        cout << firstName << endl;
    }

    // --- Right-angled triangle ---
    int fullNameLen = 0;
    for (int i = 0; i < fullName.length(); i++) {
        if (fullName[i] != ' ') fullNameLen++;
    }
    cout << "\nTriangle (height = " << fullNameLen << "):" << endl;
    for (int i = 1; i <= fullNameLen; i++) {
        for (int j = 0; j < i; j++) {
            cout << "*";
        }
        cout << endl;
    }

    
    int lastDigit = studentNumber[studentNumber.length() - 1] - '0';
    cout << "\nTimes Table for " << lastDigit << " (last digit of " << studentNumber << "):" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << lastDigit << " x " << i << " = " << lastDigit * i << endl;
    }

    return 0;
}