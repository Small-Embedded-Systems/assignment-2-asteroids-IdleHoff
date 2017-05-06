/* Asteroids view
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* hardware platform libraries */
#include <display.h>
#include <mbed.h>

#include "asteroids.h"
#include "model.h"
#include "utils.h"
#include "view.h"

extern "C" uint8_t flip(uint8_t);

Display *graphics = Display::theDisplay();
void drawSideBar(int score, float elapsed_time, int lives);
void drawShip(struct ship);
void transformShape();
void drawMissiles(struct missile *lst);
void drawRocks(struct rock *lst);

uint8_t flip(uint8_t); //assembly function for flipping image bit pattern
void rock_flip();
uint8_t flippedRock[200];

float currentHeadingForAllMissiles;


const colour_t background = rgb(0,51,102); /* Midnight Blue */
const colour_t missileColour = rgb(255,51,51); /* Red */
const colour_t shipColour = rgb(0,255,0); /* Green */
const colour_t asteroidColour = rgb(64,64,64); /* Grey */


const coordinate_t shape[] = {
    {0.0f,-10.0f}, {5.0f,5.0f}, {-5.0f,5.0f}
};
coordinate_t transformedShip[3];



/* double buffering functions */
void init_DBuffer(void)
{   /* initialise the LCD driver to use second frame in buffer */
    uint16_t *bufferbase = graphics->getFb();
    uint16_t *nextbuffer = bufferbase+ (480*272);
    LPC_LCD->UPBASE = (uint32_t)nextbuffer;
}

void swap_DBuffer(void)
{   /* swaps frames used by the LCD driver and the graphics object */
    uint16_t *buffer = graphics->getFb();
    graphics->setFb( (uint16_t*) LPC_LCD->UPBASE);
    LPC_LCD->UPBASE = (uint32_t)buffer;
}




void draw(void)
{
    graphics->fillScreen(background);
	
		drawSideBar(score, elapsed_time, lives);
		drawMissiles(shots);
		drawRocks(asteroids);
		transformShape();
		drawShip(player);
	
		if( paused ){
			graphics->setCursor(182,150);
			graphics->printf("paused"); 
		}  
    swap_DBuffer();
}

void drawSideBar(int score, float elapsed_time, int lives){
	graphics->fillRect(400, 0, 80, 272, BLACK);
	graphics->setCursor(405,5);
	graphics->printf("CM0506");
	graphics->setCursor(405, 15);
	graphics->printf("ASTEROIDS");
	graphics->setCursor(405,45);
	graphics->printf("Score: %d", score);
	graphics->setCursor(405,65);
	graphics->printf("Time : %.2f", elapsed_time);
	graphics->setCursor(405,85);
	graphics->printf("Lives: %d", lives);
	
	graphics->setCursor(405,155);
	graphics->printf("by R.Endeley");
	
	
	//testing stuff
	graphics->setCursor(405,200);
	graphics->printf("Heading: %.0f", player.heading);	
	graphics->setCursor(405,215);
	graphics->printf("x: %.0f", player.p.x);
	graphics->setCursor(405,230);
	graphics->printf("y: %.0f", player.p.y);


	
}

void drawShip(struct ship){
	graphics->drawLine(player.p.x+transformedShip[0].x, player.p.y+transformedShip[0].y, player.p.x+transformedShip[1].x, player.p.y+transformedShip[1].y, shipColour);
	graphics->drawLine(player.p.x+transformedShip[1].x, player.p.y+transformedShip[1].y, player.p.x+transformedShip[2].x, player.p.y+transformedShip[2].y, shipColour);
	graphics->drawLine(player.p.x+transformedShip[2].x, player.p.y+transformedShip[2].y, player.p.x+transformedShip[0].x, player.p.y+transformedShip[0].y, shipColour);
	currentHeadingForAllMissiles = player.heading;
}

void transformShape(){
	int i;
	for(i = 0; i < 3 ; i++){
		transformedShip[i].x = (shape[i].x*cos(radians(player.heading))) - (shape[i].y*sin(radians(player.heading)));	
		transformedShip[i].y = (shape[i].x*sin(radians(player.heading))) + (shape[i].y*cos(radians(player.heading)));	
	}
}

void drawMissiles(struct missile *lst){
	while(lst){
		graphics->fillCircle(lst->p.x, lst->p.y, 1, missileColour);
		lst = lst->next;
	}
}

void drawRocks(struct rock *lst){
	rock_flip();
	while(lst){
		graphics->drawBitmap(lst->p.x-20, lst->p.y-20, flippedRock, asteroid_width, asteroid_height, asteroidColour);
		lst = lst->next;
	}	
}

void rock_flip(){
	int i;
	for (i=0; i < 200; i++){
		flippedRock[i] = flip(asteroid_bits[i]);
	}
}

void gameover(){
	
}
