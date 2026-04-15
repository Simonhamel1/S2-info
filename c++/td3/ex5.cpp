#include<cstdlib>
#include<iostream>

using namespace std;

class Fraction{
    private:
        int numerateur;
        int denominateur;
    public:
        Fraction(int num, int deno){
            numerateur = num;
            denominateur = deno;
        }
        Fraction operator+(Fraction F){
            int num = F.numerateur*denominateur + numerateur*F.denominateur;
            int den = F.denominateur*denominateur ;
            Fraction result(num,den);
            return result;
        }
        Fraction operator*(Fraction F){
            int num = F.numerateur*numerateur;
            int den = F.denominateur*denominateur ;
            Fraction result(num,den);
            return result;
        }
        friend ostream& operator<<(ostream& os, Fraction f){
            os << "(" << f.demander_num() << "," << f.demander_deno() << ")" << endl;
            return os;
        }
        int demander_num(){
            return numerateur;
        }
        int demander_deno(){
            return denominateur;
        }
};

int main(){
    Fraction f1(7,5);
    Fraction f2(3,5);
    Fraction f3 = f1 + f2;
    Fraction f4 = f1 * f2;
    cout << f1;
    cout << f2;
    cout << f3;
    cout << f4;
    return 0;
}