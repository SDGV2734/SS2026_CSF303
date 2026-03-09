#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

class Student {
private:
    string name;
    int studentNumber;
    vector<float> marks;

public:

    Student(string n, int sn) {
        name = n;
        studentNumber = sn;
    }


    void addMark(float m) {
        marks.push_back(m);
    }


    float getAverage() {
        if (marks.empty()) return 0;
        return accumulate(marks.begin(), marks.end(), 0.0f) / marks.size();
    }


    float getHighest() {
        if (marks.empty()) return 0;
        return *max_element(marks.begin(), marks.end());
    }


    float getLowest() {
        if (marks.empty()) return 0;
        return *min_element(marks.begin(), marks.end());
    }


    string getClassification() {
        float avg = getAverage();
        if      (avg >= 75) return "Distinction";
        else if (avg >= 60) return "Merit";
        else if (avg >= 40) return "Pass";
        else                return "Fail";
    }


    void printReport() {

        cout << left << setw(20) << "Student Name"
             << ": " << name << endl;
        cout << left << setw(20) << "Student No"
             << ": " << studentNumber << endl;
        cout << left << setw(20) << "Marks Entered"
             << ": " << marks.size() << endl;

        cout << left << setw(20) << "Marks" << ": ";
        for (float m : marks) cout << m << " ";
        cout << endl;

        cout << left << setw(20) << "Average"
             << ": " << fixed << setprecision(2) << getAverage() << endl;
        cout << left << setw(20) << "Highest"
             << ": " << getHighest() << endl;
        cout << left << setw(20) << "Lowest"
             << ": " << getLowest() << endl;
        cout << left << setw(20) << "Classification"
             << ": " << getClassification() << endl;

    }
};

int main() {
    Student s("sonam dorji", 230299);

    s.addMark(88);
    s.addMark(76);
    s.addMark(91);
    s.addMark(65);
    s.addMark(83);

    s.printReport();

    return 0;
}