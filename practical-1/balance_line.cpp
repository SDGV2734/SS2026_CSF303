#include <iostream>
#include <deque>
#include <string>
using namespace std;

void printDeque(const deque<int>& dq) {
    if (dq.empty()) {
        cout << "Line is empty" << endl;
    } else {
        for (int val : dq) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    deque<int> line;
    string operation;
    int value;

    cout << "Enter operations (push_front, push_back, pop_front, pop_back):" << endl;
    cout << "Enter 'end' to stop." << endl;

    while (true) {
        cout << "\nOperation: ";
        cin >> operation;

        if (operation == "end") break;

        if (operation == "push_front") {
            cin >> value;
            line.push_front(value);
            cout << "Added " << value << " at front. Line: ";
            printDeque(line);
        }
        else if (operation == "push_back") {
            cin >> value;
            line.push_back(value);
            cout << "Added " << value << " at back. Line: ";
            printDeque(line);
        }
        else if (operation == "pop_front") {
            if (!line.empty()) {
                cout << "Removed " << line.front() << " from front. Line: ";
                line.pop_front();
                printDeque(line);
            } else {
                cout << "Line is empty!" << endl;
            }
        }
        else if (operation == "pop_back") {
            if (!line.empty()) {
                cout << "Removed " << line.back() << " from back. Line: ";
                line.pop_back();
                printDeque(line);
            } else {
                cout << "Line is empty!" << endl;
            }
        }
        else {
            cout << "Invalid operation!" << endl;
        }
    }

    return 0;
}