void loadTiles(SDL_Renderer *s, Map *m);
Map *loadMap(char *filename);
SDL_Renderer *openWindow(int w,int h);
void paint(SDL_Renderer *s,Map *m);
void recherchePointDepart(Map *m);
void loadCars(Map *m);

void showCars(SDL_Renderer *r, Map *m);
