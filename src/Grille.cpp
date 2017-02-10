#ifndef LIST
#define LIST
#include <list>
#endif

#ifndef NOEUD_CPP
#define NOEUD_CPP
#include "Noeud.cpp"
#endif

#ifndef LIEN_CPP
#define LIEN_CPP
#include "Lien.cpp"
#endif

#ifndef FONCTIONS_CPP
#define FONCTIONS_CPP
#include "Fonctions.cpp"
#endif

class Grille {
	public:
	Grille();
	void afficher();

	void newn(double, double);
	void newl(Noeud*, Noeud*);

	void deln(Noeud);

	void setdt(double);

	void calca();
	void calcv();
	void calcp();
	void avancerdt();

	void setlimite(double, double, double, double);
	void setfrottement(double);
	void stabiliser();

	double gett();
	double getlimitexm();
	double getlimitexp();
	double getlimiteym();
	double getlimiteyp();

	void setstabilisation(double);

	double amax();

	bool existe(double, double);
	bool stable();

	std::list<Noeud> tabn;
	std::list<Lien> tabl;

	private:
	double limitexm;
	double limitexp;
	double limiteym;
	double limiteyp;
	double gravite;
	double dt;
	double frottement;
	double t;
	double a_stabilisation;
};

void Grille::deln(Noeud N) {
	for(int i = 0; i < 15; i++)
		for(std::list<Lien>::iterator itl = this->tabl.begin(); itl != this->tabl.end(); itl++)
			if(*(itl->getN1()) == N or *(itl->getN2()) == N) {
				this->tabl.remove(*itl);
				break;
			}
	this->tabn.remove(N);
}

bool Grille::stable() {
	return not(this->amax() > this->a_stabilisation);
}

double Grille::gett(){
	return this->t;
}

double Grille::getlimitexm(){
	return this->limitexm;
}


double Grille::getlimitexp(){
	return this->limitexp;
}

double Grille::getlimiteym(){
	return this->limiteym;
}

double Grille::getlimiteyp(){
	return this->limiteyp;
}

void Grille::setstabilisation(double s) {
	this->a_stabilisation = s;
}

void Grille::avancerdt() {
  calca();
  calcv();
  calcp();
  t += dt;
}

double Grille::amax(){
  double maxi = 0;
  for(std::list<Noeud>::iterator it = this->tabn.begin(); it!= this->tabn.end(); it++)
    if(it->geta() > maxi)
      maxi = it->geta();
  return maxi;
}

void Grille::stabiliser() {
  for(int i = 0; i < 10; i++) this->avancerdt();
  while(not this->stable()){
    this->avancerdt();
  }
}

void Grille::calca() {
  for (std::list<Noeud>::iterator it = this->tabn.begin(); it != this->tabn.end(); it++) {
    if (not it->getfixe()) {
      //std::cout << "==========\nEn train de considerer le noeud " << i << "\n";
      double ax = - this->frottement * longueur(it->getvx(), it->getvy()) * it->getvx();
      double ay = - this->frottement * longueur(it->getvx(), it->getvy()) * it->getvy() - this->gravite * it->getmasse();
      for (std::list<Lien>::iterator itl = this->tabl.begin(); itl != this->tabl.end(); itl++) {
        //std::cout << "En train de considerer le lien " << j << "\n";
        Noeud* No;
        // std::cout << this->tabl[j].getN1() << " " << this->tabl[j].getN2() <<
        // " égales à
        // " << &(this->tabn[i]) << " ?\n";
		if (*itl->getN1() == *it) {
          No = itl->getN2();
        }

        if (*itl->getN2() == *it) {
          No = itl->getN1();
        }

        if (*itl->getN1() == *it or *itl->getN2() == *it) {
          double coef = (itl->getlongueur() - itl->getx0()) / itl->getlongueur();
          ax += - itl->getk() * (it->getx() - No->getx()) * coef;
          ay += - itl->getk() * (it->gety() - No->gety()) * coef;
        }
      }
      ax /= it->getmasse();
      ay /= it->getmasse();
      //std::cout << "Noeud " << i << " : " << ax << ":" << ay << "\n";
      it->setax(ax);
      it->setay(ay);
    }
  }
}

void Grille::calcv() {
	for (std::list<Noeud>::iterator it = this->tabn.begin(); it != this->tabn.end(); it++)
		if (not it->getfixe()) {
			it->setvx(it->getvx() + it->getax() * this->dt);
			it->setvy(it->getvy() + it->getay() * this->dt);
		}
}

void Grille::calcp() {
  for (std::list<Noeud>::iterator it = this->tabn.begin(); it != this->tabn.end(); it++) {
    it->setx(it->getx() + it->getvx() * this->dt);
    it->sety(it->gety() + it->getvy() * this->dt);
    if(it->getx() > this->limitexp)
		it->setx(this->limitexp);
	if(it->getx() < this->limitexm)
		it->setx(this->limitexm);
	if(it->gety() > this->limiteyp)
		it->sety(this->limiteyp);
	if(it->gety() < this->limiteym)
		it->sety(this->limiteym);
  }
}

Grille::Grille()
    : gravite(9.81), dt(0.01), frottement(.5), t(0), a_stabilisation(1e-5) {
  this->afficher();
}

void Grille::setdt(double dt) {
  this->dt = dt;
}

void Grille::setfrottement(double f) {
	this->frottement = f;
}

bool Grille::existe(double x, double y) {
  bool exi = false;
  for(std::list<Noeud>::iterator it = this->tabn.begin(); it != this->tabn.end(); it++) {
    if (it->getx() == x and it->gety() == y) {
      exi = true;
      break;
    }
  }
  return exi;
}

void Grille::newn(double x, double y) {
  if(!this->existe(x, y)) {
    this->tabn.push_back(Noeud(x, y));
    this->afficher();
  }
  else {
    std::cout << "Erreur : Il y a déjà un noeud ici.";
  }
}

void Grille::newl(Noeud* n1, Noeud* n2) {
  if(n1 != n2) {
    this->tabl.push_back(Lien(n1, n2));
    this->tabl.back().setx0(this->tabl.back().getlongueur());
  }
  else {
    std::cout << "Erreur : Tentative de création d'un lien entre 1 noeud";
  }
}

void Grille::setlimite(double xm, double xp, double ym, double yp) {
	this->limitexm = xm;
	this->limitexp = xp;
	this->limiteym = ym;
	this->limiteyp = yp;
}

void Grille::afficher() {
  std::cout << "\n";
  std::cout << "==========================\n";
  std::cout << "Grille " << this << "\n";
  std::cout << "Gravite = " << this->gravite << " m²/s\n";
  std::cout << "t = " << this->t << " s\n";
  std::cout << "dt = " << this->dt << " s\n";

  for (std::list<Noeud>::iterator it = this->tabn.begin(); it != this->tabn.end(); it++)
    it->afficher();
  for (std::list<Lien>::iterator itl = this->tabl.begin(); itl != this->tabl.end(); itl++)
    itl->afficher();

    std::cout << "==========================\n";
}
