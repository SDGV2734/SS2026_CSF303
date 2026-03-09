#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string fullName = "Sonam Dorji Ghalley";

    // Total length including spaces
    int totalLength = fullName.length();

    // Uppercase
    string upper = fullName;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);

    // Lowercase
    string lower = fullName;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    // Initials: first character of each word
    string initials = "";
    initials += fullName[0];
    initials += '.';
    for (int i = 1; i < fullName.length(); i++) {
        if (fullName[i] == ' ' && i + 1 < fullName.length()) {
            initials += fullName[i + 1];
            initials += '.';
        }
    }

    // First name length
    int firstNameLen = fullName.find(' ');

    cout << "Full Name      : " << fullName << endl;
    cout << "Total Length   : " << totalLength << endl;
    cout << "Uppercase      : " << upper << endl;
    cout << "Lowercase      : " << lower << endl;
    cout << "Initials       : " << initials << endl;
    cout << "First Name Len : " << firstNameLen << endl;

    return 0;
}
