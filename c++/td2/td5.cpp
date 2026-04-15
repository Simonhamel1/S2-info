#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
    int * tab = new int[100];

    for (int i=0; i<100; i++){
        tab[i] = i;
    }
    for (int i = 0; i<100; i++){
        cout << tab[i] << endl;
    }
    delete[] tab;
    return 0;
}