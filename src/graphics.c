#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <time.h>
#include "engine.h"
#include "graphics.h"
#include "timer.h"

/* Toutes les tuiles du jeu */
SDL_Texture *tile[ALL];
/*  
   Doit etre avec le meme ordre que l'enum dans le .h 
*/
const char *tilenames[] = {
		"/home/vincent/ClionProjects/commute/data/ambulance.bmp",
		"/home/vincent/ClionProjects/commute/data/minitruck.bmp",
		"/home/vincent/ClionProjects/commute/data/taxi.bmp",
		"/home/vincent/ClionProjects/commute/data/sport.bmp",
		"/home/vincent/ClionProjects/commute/data/minivan.bmp",
		"/home/vincent/ClionProjects/commute/data/truck.bmp",
		"/home/vincent/ClionProjects/commute/data/car.bmp",
		"/home/vincent/ClionProjects/commute/data/police.bmp",
		"/home/vincent/ClionProjects/commute/data/viper.bmp"
};

/* Lit un pixel d'une carte. A utiliser dans loadMap.
   Retourne la couleur RGB du pixel aux coordonnées x,y.
   DEJA ECRIT
*/
int getpixel(SDL_Surface *surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 r, g, b, *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;
	Uint32 pixel;
	switch (bpp) {
		case 1:
			pixel = *p;
			break;
		case 2:
			pixel = *(Uint16 *) p;
			break;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) pixel = p[0] << 16 | p[1] << 8 | p[2];
			else pixel = p[0] | p[1] << 8 | p[2] << 16;
			break;
		case 4:
			pixel = *(Uint32 *) p;
			break;
		default:
			pixel = 0;
	}
	//printf(">>%d %d\n", surface->pitch, surface->format->BytesPerPixel);
	SDL_GetRGB(pixel, surface->format, &r, &g, &b);
	r = r >> 4;
	g = g >> 4;
	b = b >> 4;
	return (r << 8) + (g << 4) + b;
}

/* Charge toutes les tuiles du jeu
   DEJA ECRIT
 */
void loadTiles(SDL_Renderer *s, Map *m) {
	int i, j, k;
	//SDL_SetRenderDrawColor(s, 0, 0, 0, 0);
	SDL_Texture *t = SDL_CreateTextureFromSurface(s, m->surface);
	m->tex = t;
	for (i = 0; i < ALL; i++) {
		SDL_Surface *loadedImage = SDL_LoadBMP(tilenames[i]);
		if (loadedImage != NULL) {
			Uint32 colorkey = SDL_MapRGB(loadedImage->format, 0xff, 0xff, 0xff);
			SDL_SetColorKey(loadedImage, SDL_TRUE, colorkey);
			tile[i] = SDL_CreateTextureFromSurface(s, loadedImage);
			SDL_FreeSurface(loadedImage);
		} else fprintf(stderr, "Missing file %s:%s\n", tilenames[i], SDL_GetError());
	}
}

/* Lecture d'une carte, comme MAP
   A REMPLIR
*/
Map *loadMap(char *filename) {
	SDL_Surface *s = SDL_LoadBMP(filename);

	Map *m = (Map *) malloc(sizeof(Map));
	//Car *car = (Car *) malloc(sizeof(Car));
	//car->orientation = 0.0f;
	m->hauteur = 800;
	m->largeur = 1280;
	Car car;
	car.orientation = 0.0;
	car.pos.x = 40;
	car.pos.y = 40;
	car.type = VIPER;
	car.vitesse = 3;
	car.braquage = 6;
	m->surface = s;
	recherchePointDepart(m);
	printf("Nb de point bleu : %d \r", m->nbPointsBleu);
	srand(time(NULL));
	int point = rand() % m->nbPointsBleu;
	car.pos.x = m->pointsBleu[point].x - (car.pos.x / 2);
	car.pos.y = m->pointsBleu[point].y - (car.pos.y / 2);
	/*
	int pointOrientation = 0;
	for (int x = m->car.pos.x - 3; x < m->car.pos.x + 3; x++) {
		for (int y = m->car.pos.y -3; y < m->car.pos.y + 3; y++) {
			pointOrientation = getpixel(m->surface, x, y);
			printf("x : %d y : %d \r", x, y);
			//printf("Couleur : %04x \r", pointOrientation);
			if(pointOrientation == 0xF00) {
				printf("POINT ROUGE");
			}
		}
	}
	 */

	m->car = car;

	loadCars(m);

	return m;
}

void recherchePointDepart(Map *m) {
	int pixel = 0;
	m->pointsBleu = (Point *)malloc(sizeof(Point));
	m->nbPointsBleu = 0;
	for (int h = 0; h < m->hauteur-1; h++) {
		for (int l = 0; l < m->largeur-1; l++) {
			pixel = getpixel(m->surface, l, h);
			if (pixel == 0x00f) {
				Point point;
				point.x = l;
				point.y = h;
				m->pointsBleu = (Point *)realloc(m->pointsBleu, (m->nbPointsBleu + 1) * sizeof(Point));
				m->pointsBleu[m->nbPointsBleu] = point;
				m->nbPointsBleu += 1;
			}
		}
	}
}

void loadCars(Map *m) {
	m->cars = (Car *) malloc(sizeof(Car));
	int i;
	for (i = 1; i < 10; i++) {
		Car car2;
		car2.braquage = 4;
		car2.orientation = 0;
		car2.vitesse = 2;
		car2.pos.x = i * 50;
		car2.pos.y = i * 50;
		car2.type = VIPER;

		SDL_Rect rect;
		rect.h = 32;
		rect.w = 32;
		rect.x = i * 50;
		rect.y = i * 50;

		car2.rect = rect;
		m->cars = (Car *) realloc(m->cars, i * sizeof(Car));
		m->cars[i-1] = car2;
	}
	m->nbCars = i;
}

/* Initialisation de la bibliotheque SDL, ouverture d'une fenetre de taille 
   w*SIZE x h*SIZE
 */
SDL_Renderer *openWindow(int w, int h) {
	SDL_Window *sdlWindow;
	SDL_Renderer *sdlRenderer;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Initialization error:%s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);
	if (SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_RESIZABLE, &sdlWindow, &sdlRenderer)) {
		fprintf(stderr, "Couldn't create window and renderer: %s", SDL_GetError());
		exit(1);
	}
	SDL_RenderSetLogicalSize(sdlRenderer, w, h);
	return sdlRenderer;
}

/* Redessine la carte, les joueurs, les effets, ...
*/
void paint(SDL_Renderer *r, Map *m) {
	/* Fait un ecran noir */
	//SDL_SetRenderDrawColor(r, 0, 0, 0, 255 );
	SDL_RenderClear(r);
	SDL_Rect rect;
	rect.h = m->hauteur;
	rect.w = m->largeur;
	rect.x = 0;
	rect.y = 0;
	SDL_RenderCopy(r, m->tex, NULL, &rect);
	rect.h = 32;
	rect.w = 32;
	rect.x = m->car.pos.x;
	rect.y = m->car.pos.y;
	SDL_RenderCopyEx(r, tile[m->car.type], NULL, &rect, m->car.orientation, NULL, SDL_FLIP_NONE);

	showCars(r, m);
	/* Definir ici le contenu graphique de la fenetre.
	 */

	/* Affiche le tout  */
	SDL_RenderPresent(r);
}

void showCars(SDL_Renderer *r, Map *m) {
	for (int i=0; i < 10; i++) {
		SDL_RenderCopyEx(r, tile[m->cars[i].type], NULL, &m->cars[i].rect, m->cars[i].orientation, NULL, SDL_FLIP_NONE);
	}
}
