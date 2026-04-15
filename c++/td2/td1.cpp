#include <iostream>
#include <cstdlib>

using namespace std;

class CompteBancaire {
    private:
        double solde;

    public:
        CompteBancaire(double s): solde(s){}

        int deposer(double s){
            solde += s;
            return 0;
        }
        int retirer(double s){
            solde -= s;
            if (solde < 0){
                cout << "Va bien de faire foutre tu n'a plus d'argent sur ton compte tu es runié";
            }
            return 0;
        }
        void get_solde(){
            cout << "Le solde est de " << solde << endl;
        }
};


int main(){
    CompteBancaire Simon(10);
    Simon.get_solde();
    Simon.deposer(100);
    Simon.get_solde();
    Simon.retirer(150);
    Simon.get_solde();
}