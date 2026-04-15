#include "library.hpp"

Arme::Arme(string nom, int degats) : m_nom(nom), m_degats(degats)
{
 
}
 
void Arme::changer(string nom, int degats)
{
    m_nom = nom;
    m_degats = degats;
}
 
void Arme::afficher() const
{
    cout << "Arme : " << m_nom << " (Degats : " << m_degats << ")" << endl;
}

int Arme::getDegats() const
{
    return m_degats;
}

string Arme::getNom() const
{
    return m_nom;
}

Arme::~Arme()
{
    cout << "L'arme " << m_nom << " est détruite." << endl;
}