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
					m->car.orientation = m->car.orientation - m->car.vitesse;
					break;
				case SDLK_RIGHT:
					m->car.orientation = m->car.orientation + m->car.vitesse;
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
	double val;
	val = PI / 180.0;
	float x = m->car.pos.x + m->car.vitesse * cos(val * m->car.orientation);
	float y = m->car.pos.y + m->car.vitesse * sin(val * m->car.orientation);


	if (x > m->largeur - 64 || x < 0)
		x = m->car.pos.x;
	if (y > m->hauteur - 64  || y < 0)
		y = m->car.pos.y;

	m->car.pos.x = x;
	m->car.pos.y = y;
}
