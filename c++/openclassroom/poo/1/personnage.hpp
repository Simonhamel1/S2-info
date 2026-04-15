#ifndef DEF_PERSONNAGE
#define DEF_PERSONNAGE
#include "library.hpp"

class Personnage
{
    private:
        string m_nom;
        int m_vie;
        int m_mana;
        Arme m_arme;
        
    public:
        Personnage(string nom, int vie, int mana, const Arme& arme);
        void recevoirDegats(int nbDegats);
        void attaquer(Personnage &cible);
        void boirePotionDeVie(int quantitePotion);
        void changerArme(const Arme& nouvelleArme);
        void afficherEtat() const;
        bool estVivant();
        ~Personnage();
};

#endif