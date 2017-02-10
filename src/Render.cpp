#ifndef NOEUD_CPP
#define NOEUD_CPP
#include "Noeud.cpp"
#endif

#ifndef LIEN_CPP
#define LIEN_CPP
#include "Lien.cpp"
#endif

#ifndef GRILLE_CPP
#define GRILLE_CPP
#include "Grille.cpp"
#endif

#ifndef SDL2_SDL_H
#define SDL2_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef LIST
#define LIST
#include <list>
#endif

class Render {
	public:
	Render(int, int, SDL_Renderer*, Grille*);
	void Actualiser();
	void Actualiser(Noeud*);
	double pxtox(int);
	int xtopx(double);
	double pytoy(int);
	int ytopy(double);
	int getrayon();

	private:
	int taillex;
	int tailley;
	SDL_Renderer* renderer;
	int rayon;
	Grille* G;
};

Render::Render(int x, int y, SDL_Renderer* r, Grille* Gr) : taillex(x), tailley(y), renderer(r), rayon(4), G(Gr)
{

}

int Render::getrayon() {
	return this->rayon;
}


double Render::pxtox(int x) {
	return (x - this->taillex/2)/(this->taillex/(this->G->getlimitexp()-G->getlimitexm()));
}

int Render::xtopx(double x) {
	return x * this->taillex/(this->G->getlimitexp()-G->getlimitexm()) + this->taillex/2;
}

double Render::pytoy(int y) {
	return - (y - this->tailley/2)/(this->tailley/(G->getlimiteyp()-G->getlimiteym()));
}

int Render::ytopy(double y) {
	return - y * this->tailley/(G->getlimiteyp()-G->getlimiteym()) + this->tailley/2;
}

void Render::Actualiser() {
	SDL_RenderClear(renderer);

	int x, y;
	for(std::list<Noeud>::iterator it = this->G->tabn.begin(); it != this->G->tabn.end(); it++) {
		x = this->xtopx(it->getx());
		y = this->ytopy(it->gety());
		for(int j = -this->rayon; j <= this->rayon; j++)
			for(int k = -this->rayon; k <= this->rayon; k++)
				if(longueur(j, k) <= this->rayon)
					SDL_RenderDrawPoint(renderer, x + j, y + k);
	}

	int x1, y1, x2, y2;
	for(std::list<Lien>::iterator itl = this->G->tabl.begin(); itl!= this->G->tabl.end(); itl++) {
		x1 = this->xtopx(itl->getN1()->getx());
		y1 = this->ytopy(itl->getN1()->gety());
		x2 = this->xtopx(itl->getN2()->getx());
		y2 = this->ytopy(itl->getN2()->gety());
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	}
}


void Render::Actualiser(Noeud* SN) {
	this->Actualiser();
	int x = this->xtopx(SN->getx());
	int y = this->ytopy(SN->gety());
	for(int j = - 2*this->rayon; j <= 2*this->rayon; j++)
		for(int k = -2*this->rayon; k <= 2*this->rayon; k++)
			if(longueur(j, k) <= 2*this->rayon)
				SDL_RenderDrawPoint(renderer, x + j, y + k);
	SDL_RenderPresent(this->renderer);
}
