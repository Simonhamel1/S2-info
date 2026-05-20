#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


// exo 1
class Etudiant{
    private :
        string nom;
        float note;
    public :
        Etudiant(string Nom = "default_name", float Note = 0){
            nom = Nom;
            note = Note;
        }
        void afficher(){
            cout << "NOM : " << nom << " Note : " << note << endl;
        }
        ~Etudiant(){
            cout << "l'étudiant : " << nom << " est supprimé"<< endl;
        };
};

class Complexe{
    private:
        float re;
        float im;
    public :
        Complexe(float reel=0, float imaginaire=0 ){
            re = reel;
            im = imaginaire;
        }
        Complexe operator+(Complexe ajout){
            return Complexe(ajout.re + re, ajout.im + im);
        }
        friend ostream& operator<<(ostream& os, Complexe a){
            os << "affichage im : "<< a.im << " reel  : " << a.re;
            return os;
        }
        float demander_re(Complexe a){
            return a.re;
        }
        float demander_im(Complexe a){
            return a.im;
        }
        ~Complexe(){
            cout << "suppr im : "<< im << " reel  : " << re << endl;
        }
};

int main(){
    // test
    Etudiant defaut;
    defaut.afficher();

    // exo 2
    Etudiant *simon = new Etudiant("simon", 15);
    simon->afficher();
    delete simon;
    
    // exo 3
    Complexe a(0,1);
    Complexe b(1,2);
    Complexe c = a+b;
    cout<<a;
    cout<<b;
    cout<<c; 
    
    return 0;
}