/*
 *--------------------------------------
 * Program Name:
 * Author:
 * License:
 * Description:
 *--------------------------------------
*/

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>
#include <debug.h>

#include "structs.h"





/* Put your function prototypes here */
void everything(void);
void drawmap(void);
void resetmap(int);
void genroom(void);
void randroom();
bool doesroomfit(int,int,int,int);
bool placeroom(int,int);


/* Put all your globals here */

//colors
int wallcolor = 0xE0;
int floorcolor = 0x27;

//drawnmap
int startx = 20; //20
int starty = 10; //10
int bsize = 4; //5

//map data
int map[80][80];
int mapw = 80;
int maph = 80;
int mapx;
int mapy;

//room variables
int minside = 5; //3
int maxside = 20; //15
int maxarea = 100;
int roomx;
int roomy;
int roomw;
int roomh;



/*RAND THING

	rand() % (max_number + 1 - minimum_number) + minimum_number

*/

void main(void) {
	gfx_Begin();
	gfx_FillScreen(0x00);
    do {
		kb_Scan();
		if (kb_Data[6] & kb_Enter){
			gfx_FillScreen(0x00);
			resetmap(0);
			everything();
		}
	} while (!(kb_Data[6] & kb_Clear));
	
    gfx_End();
}


void everything() {	
	
	genroom();
	drawmap();
	
}

void drawmap() {
	for( mapx=0; mapx<mapw; mapx++){
		for( mapy=0; mapy<maph; mapy++){
			
			switch (map[mapx][mapy]){
				case 0:
					gfx_SetColor(wallcolor);
					break;
				case 1:
					gfx_SetColor(floorcolor);
					break;
				default:
					gfx_SetColor(0x00);
					break;
			}
		
			gfx_FillRectangle((startx+(bsize*mapx)),(starty+(bsize*mapy)),bsize,bsize);
			
			
			/* GRID VISUALIZATION
			gfx_SetColor(0x74);
			gfx_Rectangle((startx+(bsize*mapx)),(starty+(bsize*mapy)),bsize,bsize);
			*/
		}
	}
}

void genroom() {
int rmax = 15;
	
	do { //make rooms until max is reached
	
		//picks random room size
		randroom();
	
		//checks if room fits or is intersecting any other room, then places	
		if (placeroom(roomw,roomh)) {
			rmax-=1;
		}
		
	} while (rmax);
}

void randroom(){
	//get new number  if below minimum
	//do {
	//	roomw = (rand() % maxside+1);
	//} while (roomw<minside);
	roomw = randInt(minside,maxside);
	
	//get new number if below minimum
	//do {
	//	roomh = (rand() % maxside+1);
	//} while (roomh<minside);
	roomh = randInt(minside,maxside);
}



bool placeroom(width,height){
	int countx;
	int county;
	int placex;
	int placey;
	int fmax = 10;
	
	/* Random Room Coords*/
	//do {
	//	placex = (rand() % 48);
	//} while ((placex+width>=mapw-1) || (placex == 0));
	placex = randInt(1, mapw-width);
	
	//do {
	//	placey = (rand() % 48);
	//} while ((placey+height>=maph-1) || (placey == 0));
	placey = randInt(1, maph-height);
	
	do {
		if (doesroomfit(placex,placey,width,height)){  //check if room fits
			/*write room to map*/
			for( countx = placex; countx < placex+width; countx++){
				for( county = placey; county < placey+height; county++){
					map[countx][county] = 1;
				}
			}
			return true;
		}
		                         // if room doesn't fit, decrease size
		fmax-=1;
		if (width > maxside) {
			width-=1;
		}
		if (height > maxside) {
			height-=1;
		}

			
	} while (fmax);
	
	return false;              //after some failed tries, it falls through
	
}

bool doesroomfit(x,y,w,h){
	int checkx;
	int checky;
		
		for (checkx = x-1; checkx <= x+w+1; checkx++){
			for (checky = y-1; checky <= y+h+1; checky++){
				if (map[checkx][checky]!=0) {
					return false;
				}
			}
		}
		
	return true;
}

void resetmap(value){
	for( mapx=0; mapx<mapw; mapx++){
		for( mapy=0; mapy<maph; mapy++){
			map[mapx][mapy] = value;
		}
	}
}
