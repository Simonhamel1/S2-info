#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Etudiant{
    private:
        string nom;
        int age;
    public:
        Etudiant(string n, int a): nom(n), age(a){}

        void afficher(){
            cout << "L'etudiant s'appelle " << nom << " et son age est " << age << endl;
        }
        
        ~Etudiant() {
            cout << "Destruction de l'etudiant " << nom << endl;
        }
};

int main(){
    Etudiant Simon("simon", 20);
    Simon.afficher();
}