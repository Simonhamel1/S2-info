#include "library.hpp"

Personnage::Personnage(string nom, int vie, int mana, const Arme& arme)
    : m_nom(nom), m_vie(vie), m_mana(mana), m_arme(arme)
{
}

void Personnage::recevoirDegats(int nbDegats)
{
    m_vie -= nbDegats;
    //On enlève le nombre de dégâts reçus à la vie du personnage

    if (m_vie < 0) //Pour éviter d'avoir une vie négative
    {
        m_vie = 0; //On met la vie à 0 (cela veut dire mort)
    }
}

void Personnage::attaquer(Personnage &cible)
{
    cible.recevoirDegats(m_arme.getDegats());
}

void Personnage::boirePotionDeVie(int quantitePotion)
{
    m_vie += quantitePotion;

    if (m_vie > 100) //Interdiction de dépasser 100 de vie
    {
        m_vie = 100;
    }
}

void Personnage::changerArme(const Arme& nouvelleArme)
{
    m_arme = nouvelleArme;
}

bool Personnage::estVivant()
{
    return m_vie > 0;
}

void Personnage::afficherEtat() const
{   
    cout << "nom : " << m_nom << endl;
    cout << "Vie : " << m_vie << endl;
    cout << "Mana : " << m_mana << endl;
    cout << "Arme : " << m_arme.getNom() << " (Degats : " << m_arme.getDegats() << ")" << endl;
}

Personnage::~Personnage()
{
    cout << "Le personnage " << m_nom << " est détruit." << endl;
}