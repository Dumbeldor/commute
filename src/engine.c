#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <math.h>
#include "engine.h"

#define PI 3.14159265

/* Capture les evenements clavier/fenetre 
    Retourne 1 si il faut quitter le jeu, 0 sinon.
    A COMPLETER
*/
int getEvent(Map *m) {
	SDL_Event event;
	/* Ecoute les événements qui sont arrivés */
	while (SDL_PollEvent(&event)) {
		/* On a fermé la fenetre -> quitter le jeu */
		if (event.type == SDL_QUIT) return 1;
		/* On a appuyé sur une touche */
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					return 1;
				case SDLK_UP:
					break;
				case SDLK_LEFT:
					m->car.orientation = m->car.orientation - m->car.braquage;
					break;
				case SDLK_RIGHT:
					m->car.orientation = m->car.orientation + m->car.braquage;
					if (m->car.orientation > 360) {
						m->car.orientation = m->car.orientation - 360;
					}
					break;
				default:;
			}
		}
	}
	return 0;
}

/* A COMPLETER */
void update(Map *m) {
	deplacerCar(m, &m->car);

	// Déplacer les voitures
	for (int i = 0; i < m->nbCars; i++) {
		deplacerCar(m, &m->cars[i]);
	}

}

void deplacerCar(Map *m, Car *car) {
	double val;
	val = PI / 180.0;
	float x = car->rect.x + car->vitesse * cos(val * car->orientation);
	float y = car->rect.y + car->vitesse * sin(val * car->orientation);


	if (x > m->largeur - 64 || x < 0)
		x = car->rect.x;
	if (y > m->hauteur - 64  || y < 0)
		y = car->rect.y;

	car->rect.x = x;
	car->rect.y = y;
}