#include <iostream>
#include <string>

using namespace std;

class Personnage {
private:
    string m_nom;
    int m_vie;
    int m_degat;

public:
    Personnage() : m_nom("Inconnu"), m_vie(100), m_degat(10) {
    }

    Personnage(string nom, int vie, int degat) : m_nom(nom), m_vie(vie), m_degat(degat) {
    }

    void afficher(){
        cout << "Nom   : " << m_nom << endl;
        cout << "Vie   : " << m_vie << endl;
        cout << "Degat : " << m_degat << endl;
        cout << "-----------------" << endl;
    }
};

int main() {
    // Utilisation du constructeur par défaut
    Personnage inconnu;
    Personnage simon("Simon", 1000, 150);
    inconnu.afficher();
    simon.afficher();

    Personnage * p_simon = new Personnage("Simon", 1000, 150);
    p_simon->afficher();
    return 0;
}