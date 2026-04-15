#include <iostream>
#include <cstdlib>

using namespace std;

class Etudiant {
    private:
        string nom;
        int age;
    public:
        Etudiant(string n, int a) : nom(n), age(a) {}
        void afficher() {
            cout << "Nom: " << nom << ", Age: " << age << endl;
        }
};

int main(){
    Etudiant *e1 = new Etudiant("Alice", 20);
    e1->afficher();
    delete e1;
    return 0;
}