#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    string fullName = "sonam dorji";
    string studentNumber = "02230299";

    int sonam_marks[5] = {85, 72, 90, 65, 78};
    int size = 5;

    // --- Compute stats ---
    int highest = sonam_marks[0];
    int lowest  = sonam_marks[0];
    double sum  = 0;

    for (int i = 0; i < size; i++) {
        if (sonam_marks[i] > highest) highest = sonam_marks[i];
        if (sonam_marks[i] < lowest)  lowest  = sonam_marks[i];
        sum += sonam_marks[i];
    }

    double average = sum / size;

    int aboveAverage = 0;
    for (int i = 0; i < size; i++) {
        if (sonam_marks[i] > average) aboveAverage++;
    }

    // --- Display header ---
    cout << "Student: " << fullName << " | No: " << studentNumber << endl;
    cout << left << setw(8) << "Index" << setw(8) << "Mark" << "Bar" << endl;

    // --- Display each mark with bar ---
    for (int i = 0; i < size; i++) {
        string bar = "";
        for (int j = 0; j < sonam_marks[i] / 10; j++) {
            bar += "*";
        }
        cout << left << setw(8) << ("[" + to_string(i) + "]")
             << setw(8) << sonam_marks[i]
             << bar << endl;
    }

    // --- Display summary ---
    cout << "Highest      : " << highest << endl;
    cout << "Lowest       : " << lowest  << endl;
    cout << "Average      : " << fixed << setprecision(2) << average << endl;
    cout << "Above Average: " << aboveAverage << " mark(s)" << endl;

    return 0;
}