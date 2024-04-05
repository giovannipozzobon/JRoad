#include <stdlib.h>
#include <stdbool.h>
#include "sprite.h"
#include "api.h"

volatile Car player = {ID_PLAYER, FIRST_POS_X_PLAYER,FIRST_POS_Y_PLAYER, IMAGE_PLAYER};

void spriteCommonInfo (Car *enemy, int index){

}

void create_spaceship(Car *sprite, int index){

};

void create_aircraft(Car *sprite, int index, uint8_t delay){
};

void create_spaceship_array(Car *sprite, int index){
};

void create_ghost(Car *sprite, uint8_t nr_sprite_type_ghost, int index, uint8_t delay){

};



 void changeDirectionEnemyArray(Car *enemy){
	
}


void changeDirectionEnemy(int nr_enemies){
	
}



int checkHitCar_Player(){
}
