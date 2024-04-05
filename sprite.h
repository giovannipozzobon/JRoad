#include <stdint.h>
#include <stdbool.h>
#include "global.h"


typedef struct {
	uint8_t id;
    int x, y;
    uint8_t image;
   	uint8_t nr_on_type; //number of sprite inside gruop of sprite of the type Use only by th enemy
	uint8_t type;
	uint8_t array;
	int delay; // wait X ciclies before move
    uint8_t velocity; // velocity change the delay of scroll
    bool gear; // gear of player car High (true) or low (false)
	int count_delay; // wait X ciclies before move
	bool visible;
	uint8_t ptr_mov;
} Car;

void create_Car_Player(Car *car, int index);

void create_car(Car *sprite, int index, uint8_t delay);

void create_car_array(Car *sprite, int index);

void create_ghost(Car *sprite, uint8_t nr_sprite_type_ghost, int index, uint8_t delay);

void moveEnemy(Car *enemy, Car *player);

int checkHitCar_Player();
