#include <iostream>
#include <cstdlib>
#include <string>

const double PI = 3.14159265358979323846;

class Forme{
public:
	virtual double aire() const = 0;
	virtual ~Forme() = default;
};

class Cercle : public Forme {
private:
	double rayon;

public:
	explicit Cercle(double r) : rayon(r) {}

	double aire() const override {
		return PI * rayon * rayon;
	}
};

class Rectangle : public Forme {
private:
	double largeur;
	double hauteur;

public:
	Rectangle(double l, double h) : largeur(l), hauteur(h) {}

	double aire() const override {
		return largeur * hauteur;
	}
};

int main() {
	Cercle c(3.0);
	Rectangle r(4.0, 5.0);

	std::cout << "Aire du cercle : " << c.aire() << std::endl;
	std::cout << "Aire du rectangle : " << r.aire() << std::endl;

	return 0;
}