#include <iostream> 
#include <string>   
using namespace std; 

bool isLucky(int num) {
    if (num == 0) return false; 
    
    while (num > 0) {           
        int digit = num % 10;   
        if (digit != 4 && digit != 7) 
            return false;       
        num /= 10;              
    }
    
    return true;                
}

int main() {
    string n;                   
    cin >> n;                    
    
    int countLucky = 0;         
    
    for (char c : n) {          
        if (c == '4' || c == '7') 
            countLucky++;       
    }
    
    if (isLucky(countLucky))    
        cout << "YES";         
    else
        cout << "NO";           
    
    return 0;                   
}