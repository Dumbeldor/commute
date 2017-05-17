#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "engine.h"
#include "graphics.h"
#include "timer.h"
#define MAP "/home/vincent/ClionProjects/commute/data/map0.bmp"

int main(int argc,char *argv[]) {
  Map *m;
  int finished=0;
  m=loadMap(MAP);
  SDL_Renderer *r = openWindow(m->largeur,m->hauteur); /* A changer ! */
  loadTiles(r, m);
  timerInit();
  while (!finished) {
    finished=getEvent(m);
    update(m);
    paint(r,m);
    timerWait();
    }
  return 0;
}
