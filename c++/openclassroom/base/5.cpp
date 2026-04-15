#include <iostream>
#include <cstdlib>

using namespace std;

int switch_example(int value){
    switch(value){
        case 1:
            return value + 10;
        case 2:
            return value + 20;
        case 3:
            return value + 30;
        default:
            return value;
    }
}

int test_condition(int x){
    if (x < 0) {
        return -1;
    } else if (x == 0) {
        return 0;
    } else if (x > 0 and x <= 10) {
        return 10;
    } else if ((not x < 10) and x <= 20) {
        return 20;
    } else {
        return 1;
    }
}

int main(){
    int val;
    cout << "Enter an integer for switch example (1-4): ";
    cin >> val;
    cout << "Result from switch_example: " << switch_example(val) << endl;

    cout << "Enter an integer for condition test: ";
    cin >> val;
    cout << "Result from test_condition: " << test_condition(val) << endl;

    return 0;
}