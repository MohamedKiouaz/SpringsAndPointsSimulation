#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <list> 

#include "Fonctions.cpp"

#include "Lien.cpp"
#include "Grille.cpp"
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include "Render.cpp"

int main(){
	int taillex = 700;
	int tailley = 700;
	
	Grille G = Grille();
	
	G.setlimite(-10, 10, -10, 10);
	G.setdt(1e-4);
	
	G.newn(0, 9);

	G.tabn.begin()->fixer();
	
	G.setfrottement(.7);
	
	G.setstabilisation(1e-2);
		
	SDL_Window* fenetre;
	SDL_Renderer* renderer;
	SDL_Event event;
	
	if(SDL_VideoInit(NULL) < 0) {
		std::cout << "Erreur d'initialisation de la SDL : " << SDL_GetError() << "\n";
		return EXIT_FAILURE;
	}

	fenetre = SDL_CreateWindow("Simulation numérique" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , taillex , tailley , SDL_WINDOW_RESIZABLE);
	if(fenetre == NULL) {
		printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
		return EXIT_FAILURE;
	}
	
	renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer

	if(renderer == NULL)//gestion des erreurs
	{
		printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
		return EXIT_FAILURE;
	}
	
	Render MoteurRendu = Render(taillex, tailley, renderer, &G);
	MoteurRendu.Actualiser();
	int continuer = 0;
	bool afficher = true;
	bool pause = false;
	Noeud* SN = &(*G.tabn.begin());
	Noeud* S = &(*G.tabn.begin());
	bool nouveau;
    while (!continuer)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_QUIT :
                case SDLK_ESCAPE:
					continuer = 1;
					break;
                case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_DELETE:
							G.deln(*SN);
							SN = &(*G.tabn.begin());
							break;
						/*case SDLK_KP_0:
							G.newl(&G.tabn[G.getnbn()-1], &G.tabn[0]);
							break;
						case SDLK_KP_1:
							G.newl(&G.tabn[G.getnbn()-1], &G.tabn[1]);
							break;
						case SDLK_KP_2:
							G.newl(&G.tabn[G.getnbn()-1], &G.tabn[2]);
							break;
						case SDLK_KP_3:
							G.newl(&G.tabn[G.getnbn()-1], &G.tabn[3]);
							break;
						case SDLK_KP_4:
							G.newl(&G.tabn[G.getnbn()-1], &G.tabn[4]);
							break;
						case SDLK_KP_5:
							G.newl(&G.tabn[G.getnbn()-1], &G.tabn[5]);
							break;
						case SDLK_KP_6:
							G.newl(&G.tabn[G.getnbn()-1], &G.tabn[6]);
							break;
						case SDLK_KP_7:
							G.newl(&G.tabn[G.getnbn()-1], &G.tabn[7]);
							break;
						case SDLK_KP_8:
							G.newl(&G.tabn[G.getnbn()-1], &G.tabn[8]);
							break;
						case SDLK_KP_9:
							G.newl(&G.tabn[G.getnbn()-1], &G.tabn[9]);
							break;*/
						case SDLK_x:
							for(std::list<Lien>::iterator itl = G.tabl.begin(); itl != G.tabl.end(); itl++)
								itl->setx0(1);
							break;
						case SDLK_SPACE:
							if(pause == true)
								pause = false;
							else
								pause = true;
							break;
						case SDLK_RETURN:
							G.afficher();
							break;
						case SDLK_s:
							G.stabiliser();
							break;
						case SDLK_l:
							SN->liberer();
							break;
						
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch(event.button.button) {
						case SDL_BUTTON_LEFT:
							nouveau = true;
							for(std::list<Noeud>::iterator it = G.tabn.begin(); it != G.tabn.end(); it++) {
								if(longueur(event.button.x - MoteurRendu.xtopx(it->getx()), event.button.y - MoteurRendu.ytopy(it->gety())) < 2*MoteurRendu.getrayon()) {
									SN = &(*it);
									nouveau = false;
								}
							}
							if(nouveau == true) {
								G.newn(MoteurRendu.pxtox(event.button.x), MoteurRendu.pytoy(event.button.y));
								if (G.tabn.size()>1)
									G.newl(&G.tabn.back(), SN);
								SN = &G.tabn.back();
							}
							break;
						case SDL_BUTTON_RIGHT:
							for(std::list<Noeud>::iterator it = G.tabn.begin(); it != G.tabn.end(); it++) {
								if(longueur(event.button.x - MoteurRendu.xtopx(it->getx()), event.button.y - MoteurRendu.ytopy(it->gety())) < 2*MoteurRendu.getrayon()) {
									S = &(*it);
									nouveau = false;
								}
							}
							G.newl(S, SN);
							SN = S;
							break;
						/*case SDL_BUTTON_RIGHT:
							G.newn(MoteurRendu.pxtox(event.button.x), MoteurRendu.pytoy(event.button.y));
							G.newl(&G.tabn[G.getnbn()-1], &G.tabn[G.getnbn()-2]);
							G.tabn[G.getnbn()-1].fixer();
							break;*/
						case SDL_BUTTON_MIDDLE:
							SN->setx(MoteurRendu.pxtox(event.button.x));
							SN->sety(MoteurRendu.pytoy(event.button.y));
							SN->fixer();
							break;
					}
					break;
				default:
					
					break;
            }
        }
        
        if(pause == false) {
			for(int k = 0; k < 100; k++)
				G.avancerdt();
		}
		
		MoteurRendu.Actualiser(SN);
		
		if(G.stable() and afficher == true) {
			G.afficher();
			afficher = false;
		}
		
		if(not G.stable())
			afficher = true;
    }
	
	SDL_DestroyRenderer(renderer); 
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	
	return 0;
}
