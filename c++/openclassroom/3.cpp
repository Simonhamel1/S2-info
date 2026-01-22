#include <iostream>
#include <cstdlib>
#include <string>
#include <limits>

using namespace std;

float const pi = 3.14159265358979323846;

void echanger(int a, int b){
    cout << "(a,b) : " << "(" << a << "," << b << ")" << endl;
    swap(a,b);
    cout << "(a,b) : " << "(" <<a << "," << b << ")" << endl;
}

int main(){
    string str;
    int n;
    cout << "Enter a int: ";
    cin >> n;
    while (cin.fail() || n<0) {
        cerr << "Erreur: Entrée invalide pour un entier." << endl;
        cin.clear(); // Réinitialiser l'état de l'entrée
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorer la ligne incorrecte
        cout << "Veuillez entrer un entier valide: ";
        cin >> n;
    }
    cout << "le int renter est " << n << endl ;
    cin.ignore(); // Pour ignorer le caractère de nouvelle ligne restant dans le flux d'entrée
    cout << "entrer a string: ";
    getline(cin, str);
    string& ref = str;
    cout << "entrer encore a string: ";
    getline(cin, ref);
    cout << "le string renter est " << str << " -----> " << &str<< endl ;
    cout << "le string rentrer (ref) " << ref << " -----> " << &ref << endl;
    
    echanger(5,12);

    cout << "La valeur de pi est : " << pi << endl;

    return 0;
}