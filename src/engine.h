typedef enum {
  AMBULANCE=0,
  MINITRUCK,
  TAXI,
  SPORT,
  MINIVAN,
  TRUCK,
  CAR,
  POLICE,
  VIPER,
  ALL
} TypeCar;

typedef struct {
	float x;
	float y;
} Position;

typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	TypeCar type;
	int vitesse;
	int braquage;
	float orientation;
	Position pos;
	SDL_Rect rect;
} Car;

typedef struct {
	SDL_Surface *surface;
	SDL_Texture *tex;
	int largeur;
	int hauteur;
	int nbPointsBleu;
	Point *pointsBleu;
	Car car;
	Car *cars;
	int nbCars;
} Map;
#define SIZE 64

int getEvent(Map *m);
void update(Map *m);

void deplacerCar(Map *map, Car *car);
