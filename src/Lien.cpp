/*
Author : Mohamed Kiouaz
Please ask before using this code
*/

#ifndef NOEUD_CPP
#define NOEUD_CPP
#include "Noeud.cpp"
#endif

#ifndef FONCTIONS_CPP
#define FONCTIONS_CPP
#include "Fonctions.cpp"
#endif

class Lien {
public:
    Lien();
    Lien(Noeud*, Noeud*);
    double getk();
    void setk(double);
    double getx0();
    void setx0(double);
    void afficher();
    double getlongueur();
    Noeud* getN1();
    Noeud* getN2();

    bool operator ==(Lien);

private:
    Noeud* N1;
    Noeud* N2;
    double k;
    double x0;
};

double Lien::getlongueur()
{
    return longueur(this->N1->getx() - this->N2->getx(), this->N1->gety() - this->N2->gety());
}

bool Lien::operator ==(Lien L)
{
	if (this->N1 == L.getN1() and this->N2 == L.getN2() and this->k == L.getk() and this->x0 == L.getx0())
		return true;
	else
		return false;
}

Lien::Lien()
    : N1(NULL)
    , N2(NULL)
    , k(10)
    , x0(1)
{
}

Noeud* Lien::getN1()
{
    return this->N1;
}

Noeud* Lien::getN2()
{
    return this->N2;
}

Lien::Lien(Noeud* nn1, Noeud* nn2)
    : N1(nn1)
    , N2(nn2)
    , k(100)
    , x0(1)
{
}

double Lien::getk()
{
    return this->k;
}

void Lien::setk(double k)
{
    this->k = k;
}

double Lien::getx0()
{
    return this->x0;
}

void Lien::setx0(double x0)
{
    this->x0 = x0;
}

void Lien::afficher()
{
    std::cout << "\n";
    std::cout << "Lien " << this << "\n";
    std::cout << "Lien entre " << this->N1 << " et " << this->N2 << "\n";
    std::cout << "Raideur = " << this->k << " N/m\n";
    std::cout << "x0 = " << this->x0 << " m\n";
    std::cout << "longueur = " << this->getlongueur() << " m\n";
    std::cout << "\n";
}
