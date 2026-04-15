#include <cstdlib>
#include <iostream>

using namespace std;

class Vecteur2D{
    private:
        float x;
        float y;
    public:
        Vecteur2D( float a, float b){
            x = a;
            y = b;
        }
        Vecteur2D operator+(Vecteur2D v){
            return Vecteur2D(x + v.x, y + v.y);
        }
        bool operator==(Vecteur2D v){
            return (x == v.x && y == v.y);
        }
        friend ostream& operator<<(ostream& os, Vecteur2D v){
            os << "(" << v.demander_x() << "," << v.return_y() << ")" << endl;
            return os;
        }
        Vecteur2D operator-(Vecteur2D v){
            return Vecteur2D(x -v.x, y-v.y);
        }
        float demander_x(){
            return x;
        }
        float return_y(){
            return y;
        }
};

int main(){
    Vecteur2D v1(1.0, 2.0);
    Vecteur2D v2(3.0, 4.0);
    Vecteur2D v3 = v1 + v2;
    Vecteur2D v4 = v1 - v3;
    if (v2 == v1){
        cout << "v1 et v3 sont égal" << endl;
    }
    cout << v1;
    cout << v2;
    cout << v3;
    cout << v4;
    return 0;
}