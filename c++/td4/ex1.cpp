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

// exo 4
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

    // EXERCICE 4
    Personne* Personnes[3];
    Personnes[0] = new Personne("JeanCULTAMER");
    Personnes[1] = new Etudiant(10, "halahICE");
    Personnes[2] = new Professeur("banicaca", "mathémattttttttttttttttttttttttttiques");

    cout << "\n\nAffichage des personnes : \n\n" << endl;

    for (int i = 0; i < 3; i++) {
        Personnes[i]->afficher();
        cout << endl;
        delete Personnes[i];
    }

    // EXERCICE 5
    // EXERCICE 5
    // Personne est abstraite => instanciation directe interdite.
    // Personne ptest("X"); // erreur

    Personne* groupe[2];
    groupe[0] = new Etudiant(42, "Nina");
    groupe[1] = new Professeur("Dupont", "Physique");

    for (int i = 0; i < 2; ++i) {
        groupe[i]->afficher();
        cout << endl;
        delete groupe[i];
    }

    // EXERCICE 6
    Personne* p1 = new Etudiant(5678, "Bob");
    Etudiant* e1 = dynamic_cast<Etudiant*>(p1);
    if (e1) {
        cout << "L'étudiant s'appelle : " << e1->get_name() << endl;
    } else {
        cout << "Le cast a échoué." << endl;
    }

    delete p1;
    delete e1;

    return 0;
}