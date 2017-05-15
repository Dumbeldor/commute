void loadTiles(SDL_Renderer *s);
Map *loadMap(char *filename);
SDL_Renderer *openWindow(int w,int h);
void paint(SDL_Renderer *s,Map *m);
