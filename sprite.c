#include <stdlib.h>
#include <stdbool.h>
#include "sprite.h"
#include "api.h"

volatile Car player = {ID_PLAYER, FIRST_POS_X_PLAYER,FIRST_POS_Y_PLAYER, IMAGE_PLAYER};

volatile Car enemies[NUM_ENEMIES];

void create_car_array(Car *sprite, int index)
{}
void create_ghost(Car *sprite, uint8_t nr_sprite_type_ghost, int index, uint8_t delay)
{}

void checkHitCar_Player()
{}

void carCommonInfo (Car *enemy, int index){
	int rnd;
	
	enemy->id=index+SHIFT_ID_ENEMIES; // Add 2 because 0 e 1 are player and player's missile
	rnd=rand() % (SCREEN_WIDTH);
	if (rnd > SCREEN_WIDTH-DISTANCE_HIT_SPRITE) rnd-=20;
	enemy->x = rnd;
	rnd=rand() % (SCREEN_HEIGHT);
	if (rnd > SCREEN_HEIGHT-DASHBOARD_HEIGHT-DISTANCE_HIT_SPRITE) rnd-=20;
	enemy->y = rnd;

}

void create_car(Car *sprite, int index){
	carCommonInfo (sprite, index);
    sprite->type = SPACESHIP; 
    sprite->ptr_mov= rand()%150;
    sprite->image = IMAGE_ENEMY;
	sprite->visible=true; // make enemy visible
	DrawSprite(sprite->id, sprite->x, sprite->y, sprite->image);
};

void moveEnemy(Car *enemy, Car *player) {

	uint8_t rnd;


    // SPACESHIP is random
	if(enemy->type == SPACESHIP) {
		rnd = (rand() % (2)) + 1; 
		if(rnd == 1) enemy->x-=1;
		if(rnd == 2) enemy->x+=1;
		//if(rnd == 1) enemy->y-=1;
		//if(rnd =;= 3) enemy->y+=1;
        enemy->y++;

		// check the position.If it's out of screen or in the board
		//if (enemy->y >= SCREEN_HEIGHT-DASHBOARD_HEIGHT-HEIGHT_SPRITE_FROM_BARICENTRE) enemy->y--;
		//if (enemy->y <=0) enemy->y++;
		if (enemy->x >= SCREEN_WIDTH-WIDTH_SPRITE_FROM_BARICENTRE) enemy->x--;
		if (enemy->x <=0) enemy->x++;
        


	}
}