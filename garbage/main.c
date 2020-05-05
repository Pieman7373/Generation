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
void mapgen(void);
void genrooms(void);
void randroom(int,int,int,int);
bool placeroom(int,int);
bool doesroomfit(int,int,int,int);
void mazeworm(void);
void drawmap(void);

/* Put all your globals here */
int _x;
int x;
int y;
int _y;
int offset = 10;
int xmin = 0;
int xmax = 32;
int ymin = 0;
int ymax = 175;
int treecolor = 0x03;
int floorcolor = 0xFF;
int wallcolor = 0xE0;
int min_w = 10;
int min_h = 10;
int max_w;  //30 in the final
int max_h;  //50 in final
int num_rcands;
int room_x;
int room_y;
int room_w;
int room_h;
int count;

room_t r[5600];

int map[40][179];

void main(void) {
	gfx_Begin();
	
    do {
		kb_Scan();
		if (kb_Data[6] & kb_Enter){
			everything();
		}
	} while (!(kb_Data[6] & kb_Clear));
	
    gfx_End();
}

void everything(void){
	gfx_FillScreen(0x00);
	memset(map, 0, 7160);
	
	/* random test
	for(x=xmin;x<xmax;x++){
		for(y=ymin;y<ymax;y++){
			if (randInt(0,4) == 2){
				map[x][y] = 1;
			}
		}
	}
	*/
	
	mapgen();
	drawmap();
}

/* Put other functions here */
void drawmap() {
	for (_x=xmin;_x<xmax;_x++){
		for (_y=ymin;_y<ymax;_y++){
			if (map[_x][_y] == 0){
				gfx_SetColor(wallcolor);
			}
			if (map[_x][_y] == 1){
				gfx_SetColor(floorcolor);
			}
			gfx_SetPixel(_x+offset,_y+offset);
		}
	}
}

void mapgen() {
	count=0;
	genrooms();
	//mazeworm();
	//placeflags();
}

void genrooms() {
	int fmax=10;
	int rmax=30;
	max_w = 30;
	max_h = 50;
	
	do {
		
		randroom(min_w,max_w,min_h,max_h);	
		
		count++;
		gfx_SetColor(0x00);
		gfx_FillRectangle(150,150,80,15);
		gfx_SetTextFGColor(gfx_green);
		gfx_SetTextXY(150,150);
		gfx_PrintInt(count,8);
		
		if (placeroom(room_w, room_h)) {
			rmax--;
		} 
		else {
			fmax--;
		}
	} while (fmax > 0 && rmax > 0);
}

void randroom(int mn_w,int mx_w,int mn_h,int mx_h) {
	room_w = 10;
	room_h = 10;
	//room_w = randInt(mn_w,mx_w);
	//room_h = randInt(mn_h,mx_h);
}

bool placeroom(int w,int h) {
	int r_x;
	int r_y;
	int R;
	int rp_x;
	int rp_y;
	int mx;
	int my;
	num_rcands = 0;
	for (r_x=xmin;r_x<(xmax-w);r_x++){
		for (r_y=ymin;r_y<(ymax-h);r_y++){
			if (doesroomfit(r_x,r_y,w,h)) {
				r[num_rcands].x = r_x;
				r[num_rcands].y = r_y;
				r[num_rcands].w = w;
				r[num_rcands].h = h;
				num_rcands++;
			}
		}
	}
	if (num_rcands==0){
		return false;
	}
	R = randInt(0,num_rcands);
	for (rp_x=r[R].x;rp_x<(r[R].x+r[R].w);rp_x++){
		for (rp_y=r[R].y;rp_y<(r[R].y+r[R].h);rp_y++){
			mx=r[R].x;
			my=r[R].y;
			map[mx][my]=1;
		}
	}
	return true;
}

bool doesroomfit(int x,int y,int w,int h) {
	int r_x;
	int r_y;
	for (r_x=(x-5);r_x<x+(w+5);r_x++){
		for (r_y=(y-5);r_y<y+(h+5);r_y++){
			if (map[r_x][r_y]==1){
				return false;
			}
		}
	}
	return true;
}