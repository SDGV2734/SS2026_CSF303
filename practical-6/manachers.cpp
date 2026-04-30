#include <iostream>
#include <string>
#include <vector>

using namespace std;

string longestPalindrome(const string &text) {
    if (text.empty()) {
        return "";
    }

    string transformed = "@";
    for (char ch : text) {
        transformed += '#';
        transformed += ch;
    }
    transformed += "#$";

    vector<int> radius(transformed.size(), 0);
    int center = 0;
    int right = 0;
    int bestCenter = 0;
    int bestLength = 0;

    for (int i = 1; i < (int)transformed.size() - 1; i++) {
        int mirror = 2 * center - i;

        if (i < right) {
            radius[i] = min(right - i, radius[mirror]);
        }

        while (transformed[i + radius[i] + 1] == transformed[i - radius[i] - 1]) {
            radius[i]++;
        }

        if (i + radius[i] > right) {
            center = i;
            right = i + radius[i];
        }

        if (radius[i] > bestLength) {
            bestLength = radius[i];
            bestCenter = i;
        }
    }

    int start = (bestCenter - bestLength) / 2;
    return text.substr(start, bestLength);
}

int main() {
    vector<string> examples = {
        "babad",
        "cbbd",
        "forgeeksskeegfor",
        "abacdfgdcaba"
    };

    cout << "Manacher's Algorithm\n";
    for (const string &text : examples) {
        string palindrome = longestPalindrome(text);
        cout << "Input: " << text << '\n';
        cout << "Longest palindromic substring: " << palindrome << '\n';
        cout << "Length: " << palindrome.size() << "\n\n";
    }

    return 0;
}
