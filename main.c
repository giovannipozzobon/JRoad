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
unsigned char *ptr_room; // the room active
// map of screen
unsigned char map[1803];
// buffer for dashboard and other string to print on the screen
char buffer[41];

extern Car player;

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
}

void print_dashboard_info()
{

	// the first byte of buffer is the lentgh of string (fixed length string)
	//sprintf(buffer + 1, "SPEED %1d GEAR %1dLIFES: %1d  SCORE: %1d  LEVEL: %1d", player.velocity, player.velocity, player.velocity, player.velocity );
	SetColor(0xf0, 2, 1, 1, 0);
	sprintf(buffer + 1, "SPEED %u ", player.velocity-100);
	Gfx_WriteString(POS_DASHBOARD_INFO, SCREEN_HEIGHT - DASHBOARD_HEIGHT, buffer);
}

void check_velocity(void){
	if (player.velocity > 215) player.velocity=215;
	if (player.velocity < 100) player.velocity=100;

}

void movement(void){
	uint8_t movement;

	movement = CheckJoypad();

	if (bit_check(movement, 0))
	{
		
	} // sprite_x =-1;
	if (bit_check(movement, 1))
	{
		
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

// Funzione principale
int main() {
	uint8_t acceleration=2; 
    // Load resource file
	LoadResource();    
	player.velocity=100;

    while(1) {
        
		if (acceleration<1) {
			movement();
			if (player.velocity<190) {acceleration=2;} else {acceleration=100;}
		}
		else {
			acceleration--;
		}

		nop_delay(2200-(player.velocity*10));
		print_dashboard_info();
        Scroll();

    }
}