#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int* return_table(int tab[]){
    for(int i=0; i<5; i++){
        cout << "Element " << i << " : " << tab[i] << endl;
        tab[i] += 10;
    }
    return tab;
}

int main(){
    int my_table[5] = {1,2,3,4,5};
    int* my_table_ref = return_table(my_table);
    cout << "Table after function call:" << endl;
    for(int i=0; i<5; i++){
        cout << "Element " << i << " : " << my_table_ref[i] << endl;
    }
    return 0;
}

// int main(){
//     int a = 5;
//     int* pA = &a;
//     cout << "Value of a: " << a << endl;
//     cout << "Address of a: " << pA << endl;
// }