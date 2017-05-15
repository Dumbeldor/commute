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
	TypeCar type;
	int vitesse;
	float orientation;
	Position pos;
} Car;

typedef struct {
	SDL_Surface *surface;
	int largeur;
	int hauteur;
	Car car;
} Map;
#define SIZE 64

int getEvent(Map *m);
void update(Map *m);
