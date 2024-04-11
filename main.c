#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "global.h"
#include "pista1.h"
#include "api.h"
#include "sprite.h"
#include "utility.h"

const unsigned char nameFileGfx[] = {12, 'g', 'r', 'a', 'p', 'h', 'i', 'c', 's', '.', 'g', 'f', 'x'};

int scroll_pointer = 0, room_active = 0;
int score;
unsigned char *ptr_room; // the room active
// map of screen
unsigned char map[1803];
// buffer for dashboard and other string to print on the screen
char buffer[41];

volatile int level, lifes_player;

// total of enemies in the actual level
int total_enemies_level;

extern Car player;

extern Car enemies[];

// Type and qty of enemy for every level
// the order is SPACESHIP, AIRCRAFT, SPACESHIP_ARRAY, GHOST

const uint8_t array_enemy_for_level[NR_OF_LEVEL][NR_TYPE_OF_ENEMY] = {

	{5, 1, 1, 1},
	{3, 3, 3, 0},
	{2, 3, 0, 4},
	{2, 3, 3, 2},
	{2, 3, 3, 2},	
	{3, 3, 2, 0}
};

// velocity of enimies
const uint8_t array_delay_enemies[NR_OF_LEVEL][2] = {
	{20, 3}, {10, 5}, {5, 5}, {10, 3}, {10, 5}, {15, 13}// nr loops to wait 
};

void LoadResource()
{

	// Load graphics
	LoadGrafix(nameFileGfx);

}

bool Scroll()
{
    uint8_t i;

	if (scroll_pointer > (LENGTH_SCROLL- (SCREEN_HEIGHT- DASHBOARD_HEIGHT))) {
		scroll_pointer = 0;
		//go to next level
		//return true;
	}   


	ptr_room = (unsigned char *) &pista1[0];
	SetCurrentTileMap(ptr_room, 0, LENGTH_SCROLL - SCREEN_HEIGHT - scroll_pointer);
	DrawTileMap(0, 0, 320, SCREEN_HEIGHT - DASHBOARD_HEIGHT);

	scroll_pointer++;
	return false;
}

void Initialise()
{

	SetColor(0xf0, 7, 1, 1, 0);
	
	// sound of explosion
	ResetChannelSound(0);
	PlaySoundChannel(0, SOUND_PLAYER_HIT);

	score =0;
}

void print_dashboard_info()
{

	// the first byte of buffer is the lentgh of string (fixed length string)
	//sprintf(buffer + 1, "SPEED %1d GEAR %1dLIFES: %1d  SCORE: %1d  LEVEL: %1d", player.velocity, player.velocity, player.velocity, player.velocity );
	SetColor(0xf0, 2, 1, 1, 0);
	sprintf(buffer + 1, "SPEED %u   SCORE %u", player.velocity-100, score);
	Gfx_WriteString(POS_DASHBOARD_INFO, SCREEN_HEIGHT - DASHBOARD_HEIGHT, buffer);
}

void check_velocity(void){
	if (player.velocity > 215) player.velocity=215;
	if (player.velocity < 110) player.velocity=110;

}

void movement(void){
	uint8_t movement;

	movement = CheckJoypad();

	if (bit_check(movement, 0))
	{
		player.x--;
		if (player.x<1) player.x=1;
		MoveSprite(player.id, player.x, player.y);
	} // sprite_x =-1;
	if (bit_check(movement, 1))
	{
		player.x++;
		if (player.x>319) player.x=319;
		MoveSprite(player.id, player.x, player.y);	
	} // sprite_x =+1;
	if (bit_check(movement, 2))
	{
		player.velocity++;
	} // sprite_y =-1;
	if (bit_check(movement, 3))
	{
		player.velocity--;
	} // sprite_y =+1;
	if (bit_check(movement, 4))
	{
		player.gear = true;
	} // Fire_A
	if (bit_check(movement, 5))
	{ 
		player.gear = false;
	} // Fire_B

	// check if speed is put of range (up and down)
	check_velocity();

}

void checkHitCar_Kerbs()
{
    int posx,posy;
    uint8_t road;
    posx=player.x/16;
    posy=player.y/16;
    road=pista1[3+posy*20+posx];
    if ((road==58) || (road==59) || (road==60) || (road==61) || (road==03))
    {
        player.velocity--;
		check_velocity();
    }
}

void create_enemy()
{
	uint8_t i, nr_sprite_type_ghost = 0;

	for (i = 0; i < array_enemy_for_level[level - 1][0]; i++)
	{
		create_car(&enemies[total_enemies_level], total_enemies_level);
		total_enemies_level++;
	};


}



void moveAllEnemies()
{
	int i;

	for (i = 0; i < total_enemies_level; i++)
	{
		// move the enemies
		moveEnemy(&enemies[i], &player);
		if (enemies[i].visible == true)
			MoveSprite(enemies[i].id, enemies[i].x, enemies[i].y);
	}
}
// Funzione principale
int main() {
	uint8_t acceleration=2; 
    // Load resource file
	LoadResource();    
	player.velocity=100;
	DrawSprite(player.id, player.x, player.y, player.image);
	level =1;

	//create_enemy();

    while(1) {
        
		movement();
		score++;
		
		if (acceleration<1) {
			
			if (player.velocity<190) {acceleration=2;} else {acceleration=100;}
		}
		else {
			acceleration--;
		}

		//moveAllEnemies();
		checkHitCar_Kerbs();
		//checkHitCar_Player();
		nop_delay(2200-(player.velocity*10));
		print_dashboard_info();
        Scroll();

    }
}