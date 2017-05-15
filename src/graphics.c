#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "engine.h"
#include "graphics.h"
#include "timer.h"
/* Toutes les tuiles du jeu */
SDL_Texture *tile[ALL];
/*  
   Doit etre avec le meme ordre que l'enum dans le .h 
*/
const char *tilenames[]={
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
  Uint8 r,g,b,*p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  Uint32 pixel;
  switch(bpp) {
  case 1: pixel= *p; break;
  case 2: pixel= *(Uint16 *)p; break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) pixel= p[0] << 16 | p[1] << 8 | p[2];
    else pixel= p[0] | p[1] << 8 | p[2] << 16;
    break;
  case 4: pixel= *(Uint32 *)p; break;
  default: pixel= 0;   
  }
  printf(">>%d %d\n",surface->pitch,surface->format->BytesPerPixel);
  SDL_GetRGB(pixel, surface->format, &r, &g, &b);
  r=r>>4;
  g=g>>4;
  b=b>>4;
  return (r<<8)+(g<<4)+b;
}
/* Charge toutes les tuiles du jeu
   DEJA ECRIT
 */
void loadTiles(SDL_Renderer *s) {
  int i,j,k;
  SDL_SetRenderDrawColor(s, 0, 0, 0, 0);
  for (i=0; i<ALL; i++)  {
    SDL_Surface *loadedImage=SDL_LoadBMP(tilenames[i]);
    if (loadedImage !=NULL) {
      Uint32 colorkey = SDL_MapRGB(loadedImage->format,0xff,0xff,0xff);
      SDL_SetColorKey(loadedImage,SDL_TRUE,colorkey);
      tile[i]=SDL_CreateTextureFromSurface(s, loadedImage );
      SDL_FreeSurface(loadedImage);
    } else fprintf(stderr,"Missing file %s:%s\n",tilenames[i],SDL_GetError());
  }
}
/* Lecture d'une carte, comme MAP 
   A REMPLIR
*/
Map *loadMap(char *filename) {
  SDL_Surface *s=SDL_LoadBMP(filename);

  Map *m = (Map *) malloc(sizeof(Map));
  //Car *car = (Car *) malloc(sizeof(Car));
  //car->orientation = 0.0f;
  m->hauteur = 600;
  m->largeur = 800;
  m->car.orientation = 0.0;
  m->car.pos.x = 40;
  m->car.pos.y = 40;
  m->car.type = VIPER;
  m->car.vitesse = 5;
  m->surface = s;
  return m;
}

/* Initialisation de la bibliotheque SDL, ouverture d'une fenetre de taille 
   w*SIZE x h*SIZE
 */
SDL_Renderer *openWindow(int w,int h) {
  SDL_Window *sdlWindow;
  SDL_Renderer *sdlRenderer;
  if (SDL_Init(SDL_INIT_VIDEO)<0) {
    fprintf(stderr,"Initialization error:%s\n",SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);
  if (SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_RESIZABLE, &sdlWindow, &sdlRenderer)) {
    fprintf(stderr,"Couldn't create window and renderer: %s",SDL_GetError());
    exit(1);
  }
  SDL_RenderSetLogicalSize(sdlRenderer, w, h);
  return sdlRenderer;
}
/* Redessine la carte, les joueurs, les effets, ... 
*/
void paint(SDL_Renderer *r,Map *m) {
  /* Fait un ecran noir */
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255 );
  SDL_RenderClear(r);
  SDL_Rect rect;
  rect.h = 64;
  rect.w = 64;
  rect.x = m->car.pos.x;
  rect.y = m->car.pos.y;
	SDL_RenderCopyEx(r, tile[m->car.type], NULL, &rect, m->car.orientation, NULL, SDL_FLIP_NONE);
  /* Definir ici le contenu graphique de la fenetre.
   */

  /* Affiche le tout  */
  SDL_RenderPresent(r);
}
