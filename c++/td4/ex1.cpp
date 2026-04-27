#include <iostream>
#include <cstdlib>

using namespace std;

class Personne{
    protected:
        string nom;
    public:
        Personne(string n = "test"): nom(n){}
        virtual void afficher() const{
            cout << "Nom : " << nom << endl;
        }
    virtual ~Personne(){
            cout << "Destruction de la personne : " << nom << endl;
        }
};


class Etudiant : public Personne{
    private:
        int id;
    public:
        Etudiant(int identity_code = 8, string student_name = "default"): id(identity_code), Personne(student_name){}
        int get_name() const {
            return id;
        }
        void afficher() const{
            cout << "Id : " << id << endl;
            Personne::afficher();
        }
        ~Etudiant(){
            cout << "Destruction de l'etudiant : " << id << endl;
        }
};

class Professeur : public Personne{
    private:
        string specialite;
    public:
        Professeur(string n = "roger", string spe= "taikcuendo"): specialite(spe), Personne(n){};
        
        void afficher() const{
            cout << "Proffesseur : " << Personne::nom << ", specialité : " << specialite << endl;
        }
        ~Professeur(){
            cout << "Professeur supprimé : " << Personne::nom << endl; 
        }
};

int main(){
    Personne unePersonne("Jean"); 
    Etudiant unEtudiant(10, "Alice");
    Etudiant simon(5, "simon");

    unEtudiant.afficher();
    cout << endl;
    unePersonne.afficher();
    cout << endl;
    simon.afficher();
    cout << endl;

    Personne * p;
    Etudiant e(1234, "Alice");
    p = &e;
    p->afficher();
    cout << endl;

    Professeur prof("banicka", "maths");
    prof.afficher();
    cout << endl;

    return 0;
}