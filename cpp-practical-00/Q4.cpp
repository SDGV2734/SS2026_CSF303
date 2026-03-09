#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    string name, studentNumber;
    int age;
    int currentYear = 2026;

    cout << "Enter your name : ";
    getline(cin, name);

    cout << "Enter student number : ";
    cin >> studentNumber;

    cout << "Enter your age : ";
    cin >> age;

    int yearOfBirth = currentYear - age;
    int yearAt100 = yearOfBirth + 100;

    
    cout << "Name        : " << name << endl;
    cout << "Student No  : " << studentNumber << endl;
    cout << "Year of Birth : " << yearOfBirth << endl;
    cout << "Year at Age 100: " << yearAt100 << endl;

    return 0;
}