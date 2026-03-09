#include <iostream>
#include <string>
using namespace std;

int digitSum(int n) {
    if (n < 0) n = -n;
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int countVowels(string s) {
    int count = 0;
    for (int i = 0; i < s.length(); i++) {
        char c = tolower(s[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

string reverseString(string s) {
    string reversed = "";
    for (int i = s.length() - 1; i >= 0; i--) {
        reversed += s[i];
    }
    return reversed;
}

int main() {
    string fullName = "sonam dorji";
    long long studentNumber = 2230299;

    
    cout << "Function Results for " << fullName << endl;
    cout << "Student No: " << studentNumber << endl;
    cout << "digitSum(20240101)        : " << digitSum(studentNumber) << endl;
    cout << "isPrime(20240101)         : " << (isPrime(studentNumber) ? "Yes" : "No") << endl;
    cout << "countVowels(" << fullName << ")  : " << countVowels(fullName) << endl;
    cout << "reverseString(" << fullName << "): " << reverseString(fullName) << endl;
    

    return 0;
}