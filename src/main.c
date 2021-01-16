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
//void randroom();
bool doesroomfit(int,int,int,int);
bool placeroom(int,int);


/* Put all your globals here */

//colors
int wallcolor = 0xE0;
int floorcolor = 0x27;

//drawnmap
int startx = 20; //20
int starty = 10; //10
int bsize = 2; //5

//map da	ta
int map[100][100];
int mapw = 100;
int maph = 100;
int mapx;
int mapy;

//room variables
int minw = 5; //3
int minh = 5;
int maxw = 30; //15
int maxh = 30;
int roomx;
int roomy;

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
int rmax = 25;

	
	do { //make rooms until max is reached
	
		//checks if room fits or is intersecting any other room, then places	
		//randroom integrated into placeroom function call
		if (placeroom(randInt(minw,maxw),randInt(minh,maxh))) {
			rmax-=1;
		}
		
	} while (rmax);
}

/*
void randroom(){
	//get new number  if below minimum
	//do {
	//	roomw = (rand() % maxside+1);
	//} while (roomw<minside);
	roomw = randInt(minw,maxw);
	
	//get new number if below minimum
	//do {
	//	roomh = (rand() % maxside+1);
	//} while (roomh<minside);
	roomh = randInt(minw,maxw);
}
*/


bool placeroom(width,height){
	int countx;
	int county;
	int placex;
	int placey;
	int fmax = 10;
	
	/* Random Room Coords*/
	placex = randInt(1, mapw-width-1);
	placey = randInt(1, maph-height-1);
	
	
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
		
		switch randInt(0,1){
			case 0: 
				if (width > maxw) {
					width-=1;
				}
			case 1:
				if (height > maxh) {
					height-=1;
				}
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
