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
	int x;
	int y;
} Position;

typedef struct {
	TypeCar type;
	int vitesse;
	float orientation;
	Position pos;
} Car;

typedef struct {
	int largeur;
	int hauteur;
} Map;
#define SIZE 64

int getEvent(Map *m);
void update(Map *m);
