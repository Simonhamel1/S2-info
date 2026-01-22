#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

float aire_cercle(float rayon){
    return M_PI * rayon * rayon;
}

int calcul_complexe(int a){
    a += 10;
    a--; // Décrémenter a de 1
    --a; // Décrémenter a de 1
    a++ ; // Incrémenter a de 1
    ++a; // Incrémenter a de 1
    return a;
}

int main(){
    float r(5.0);
    cout << "L'aire du cercle de rayon " << r << " est: " << aire_cercle(r) << endl;
    cout << "Le résultat du calcul complexe est: " << calcul_complexe(5) << endl;
    return 0;
}