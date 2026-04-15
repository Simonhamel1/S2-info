#include <iostream>
#include <cstdlib>

using namespace std;

class Livre{
    private:
        char * titre;
    public:
        Livre(char * t):titre(t){}
        void afficher(){
            cout << "Le titre du livre est " << titre << endl;
        }
    ~Livre(){}
};


int main(){
    cout << "entre votre paf" << endl;
    char * titre;
    cin >> titre;
    Livre * l1 = new Livre(titre);
    l1->afficher();
    delete l1;
    return 0;
}