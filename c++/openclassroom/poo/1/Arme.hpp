#ifndef DEF_ARME
#define DEF_ARME

#include "library.hpp"

class Arme
{
    private:
        string m_nom;
        int m_degats;

    public:
        Arme(string nom, int degats);
        void changer(string nom, int degats);
        int getDegats() const;
        string getNom() const;
        void afficher() const;

    ~Arme();
};
 
#endif