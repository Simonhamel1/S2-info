#include <cstdlib>
#include <iostream>

using namespace std;

class Test{
    public:
        Test(int a){
            x = a;
        }
        int x;
        Test operator+(Test t){
            return Test(x + t.x);
        }
        Test operator-(Test t){
            return Test(x - t.x);
        }
};

int main(){
    Test t1(5);
    Test t2(10);
    Test t3 = t1 + t2;
    Test t4 = t2 - t1;
    cout << "t1: " << t1.x << endl;
    cout << "t2: " << t2.x << endl;
};