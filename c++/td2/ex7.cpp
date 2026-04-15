#include <cstdlib>
#include <iostream>

using namespace std;

class Test {
    public:
        int* data;
        Test() {
        data = new int(5);
        }
    ~Test(){
        cout << "Destroy test" << endl;
    }
};