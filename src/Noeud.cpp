#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef FONCTIONS_CPP
#define FONCTIONS_CPP
#include "Fonctions.cpp"
#endif

class Noeud
{
	public:
		Noeud();
		Noeud(double, double);

		double getmasse();
		void setmasse(double);

		void fixer();
		bool getfixe();
		void liberer();

		double getx();
		double gety();
		void setx(double);
		void sety(double);

		double getvy();
		double getvx();
		void setvy(double);
		void setvx(double);
		double getv();

		double getax();
		double getay();
		void setax(double);
		void setay(double);
		double geta();

		void afficher();

		bool operator==(Noeud);

	private:
		double x;
		double y;
		double vx;
		double vy;
		double ax;
		double ay;
		bool fixe;
		double masse;
};

Noeud::Noeud(): x(0), y(0), vx(0), vy(0), ax(0), ay(0), fixe(false), masse(1) {

}

bool Noeud::operator ==(Noeud N) {
	if (this->x == N.x and this-> y == N.y and this-> masse == N.masse and this-> fixe == N.fixe)
		return true;
	else
		return false;
}

Noeud::Noeud(double xx, double yy): x(xx), y(yy), vx(0), vy(0), ax(0), ay(0), fixe(false), masse(1) {

}

bool Noeud::getfixe() {
	return this->fixe;
}

void Noeud::fixer()
{
	this->fixe = true;
	this->ax = 0;
	this->ay = 0;
	this->vx = 0;
	this->vy = 0;
}

void Noeud::liberer()
{
	this->fixe = false;
}

double Noeud::getmasse() {
	return this->masse;
}

void Noeud::setmasse(double m) {
	this->masse = m;
}

double Noeud::getx() {
	return this->x;
}

double Noeud::gety() {
	return this->y;
}

void Noeud::setx(double x) {
	this->x = x;
}

void Noeud::sety(double y) {
	this->y = y;
}

double Noeud::getax() {
	return this->ax;
}

double Noeud::getay() {
	return this->ay;
}

double Noeud::geta() {
	return longueur(this->ax, this->ay);
}

double Noeud::getvx()
{
	return this->vx;
}

double Noeud::getvy()
{
	return this->vy;
}

double Noeud::getv() {
	return longueur(this->vx, this->vy);
}

void Noeud::setvx(double vx) {
	this->vx = vx;
}

void Noeud::setvy(double vy) {
	this->vy = vy;
}

void Noeud::setax(double ax) {
	this->ax = ax;
}

void Noeud::setay(double ay) {
	this->ay = ay;
}

void Noeud::afficher()
{
	std::cout << "\n";
	std::cout << "Noeud " << this << "\n";
	if (this->fixe)
		std::cout << "Fixé\n";
	else
		std::cout << "Mobile\n";

	std::cout << "Position : (" << this->x << ":" << this->y << ")\n";
	std::cout << "Vitesse : (" << this->vx << ":" << this->vy << ") soit " << this->getv() << " m/s\n";
	std::cout << "Acceleration : (" << this->ax << ":" << this->ay << ") soit " << this->geta() << " m²/s\n";
	std::cout << "\n";
}
