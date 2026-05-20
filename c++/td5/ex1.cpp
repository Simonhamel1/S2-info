#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int is_integer(int number) {
    return (number == static_cast<int>(number));
}

int main() {
    int number1;
    int number2;
    cout << "Enter the first number: ";
    cin >> number1;
    cout << "Enter the second number: ";
    cin >> number2;
    try {
        if (number2 == 0) {
            throw runtime_error("Division by zero je m'en balex ");
        }
        if (is_integer(number1) == false || is_integer(number2) == false) {
            throw runtime_error("Invalid input. Please enter integers only.");
        }
        int result = number1 / number2;
        cout << "The result of " << number1 << " divided by " << number2 << " is: " << result << endl;
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
