#include<cstdlib>
#include<iostream>

using namespace std;

class Tableau{
    private:
        int* tab;
        int taille;
    public:
        Tableau(int t){
            taille = t;
            tab = new int[taille];
        }
        ~Tableau(){
            delete[] tab;
        }
        int& operator[](int i){
            return tab[i];
        }
        int get_taille(){
            return taille;
        }
};

int main(){
    Tableau t(5);
    for(int i=0; i<t.get_taille(); i++){
        t[i] = i+1;
    }
    for(int i=0; i<t.get_taille(); i++){
        cout << t[i] << " ";
    }
    cout << endl;
    return 0;
}