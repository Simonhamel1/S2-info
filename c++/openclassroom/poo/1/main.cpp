#include "library.hpp"

int main()
{
    //Création des armes
    Arme epee("Epee en pierre", 15);
    Arme hache("Hache en pierre", 20);
    
    //Création des personnages
    Personnage david("David", 100, 50, epee);
    Personnage goliath("Goliath", 150, 50, hache);
 
    //Au combat !
    goliath.attaquer(david); // Goliath attaque David et lui inflige 15 points de dégâts car il utilise une épée en pierre
    david.boirePotionDeVie(20); // David boit une potion de vie et récupère 20 points de vie
    goliath.attaquer(david); // Goliath attaque à nouveau David et lui inflige 15 points de dégâts, David a donc perdu 10 points de vie
    cout << "goliath a attaqué david" << endl;
    david.afficherEtat(); // Affiche l'état de David
    david.attaquer(goliath); // David attaque Goliath et lui inflige 15 points de dégâts, Goliath a donc perdu 15 points de vie
    goliath.changerArme(hache); // Goliath change d'arme et prend une hache en pierre qui inflige 20 points de dégâts
    goliath.attaquer(david); // Goliath attaque à nouveau David et lui inflige 20 points de dégâts, David a donc perdu 30 points de vie et est mort
 
    //Temps mort ! Voyons voir la vie de chacun…
    david.afficherEtat();
    goliath.afficherEtat();
 
    return 0;
}