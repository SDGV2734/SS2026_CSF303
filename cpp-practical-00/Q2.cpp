#include <iostream>

using namespace std;

int main() {

    int studentNumber = 2230299;  // Assuming student number is an integer for this task
    int originalNumber = studentNumber;  // Saving  the original value
    int SUM = 0;
    
    while (studentNumber > 0) {
        SUM += studentNumber % 10;  // Extract last digit
        studentNumber /= 10;        // Remove last digit
    }
    
    cout << "Student No: " << originalNumber << endl;
    cout << "Sum of digits: " << SUM << endl;

    if (originalNumber % 2 == 0) {
        cout << "The student number is even." << endl;
    } else {
        cout << "The student number is odd." << endl;
    }
    
    cout << "Reminder (% 7): " << originalNumber % 7 << endl;
    cout << "Multiplied by 3: " << originalNumber * 3 << endl;

    return 0;
}
