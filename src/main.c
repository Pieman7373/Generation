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
void mapgen(void);
void genrooms(void);
void randroom(int,int,int,int);
bool placeroom(int,int);
bool doesroomfit(int,int,int,int);
void mazeworm(void);
void drawmap(void);

/* Put all your globals here */
int _x;
int _y;
int offset = 10;
int xmin = 0;
int xmax = 30;
int ymin = 0;
int ymax = 20;
int treecolor = 0x03;
int floorcolor = 0xFF;
int wallcolor = 0xE0;
int min_w = 3;
int min_h = 3;
int max_w=10;
int max_h=10;
int num_rcands;
int room_x;
int room_y;
int room_w;
int room_h;

room_t r[600];

int map[30][20];

void main(void) {
	gfx_Begin();
	
	mapgen();
	drawmap();
	
    do {
		kb_Scan();
	} while (!(kb_Data[6] & kb_Clear));
	
    gfx_End();
}

/* Put other functions here */
void drawmap() {
	gfx_FillScreen(0x00);
	for (_x=xmin;_x<xmax;_x++){
		for (_y=ymin;_y<ymax;_y++){
			if (map[_x][_y] == 1){
				gfx_SetColor(wallcolor);
			}
			else if (map[_x][_y] == 0){
				gfx_SetColor(floorcolor);
			}
			gfx_SetTextXY((_x*8)+offset,(_y*8)+offset);
			gfx_PrintStringXY("o",(_x*8)+offset,(_y*8)+offset);
		}
	}
}

void mapgen() {
	genrooms();
	//mazeworm();
	//placeflags();
}

void genrooms() {
	int fmax=10;
	int rmax=10;
	max_w = 10;
	max_h = 10;
	randroom(min_w,max_w,min_h,max_h);
	do {
		if (placeroom(room_w, room_h)) {
			rmax--;
		} 
		else {
			fmax--;
		}
	} while (fmax > 0 || rmax > 0);
}

void randroom(int mn_w,int mx_w,int mn_h,int mx_h) {
	room_w = randInt(mn_w,mx_w);
	room_h = randInt(mn_h,mx_h);
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
				r[num_rcands].x=r_x;
				r[num_rcands].y=r_y;
				r[num_rcands].w=w;
				r[num_rcands].h=h;
				num_rcands++;
			}
		}
	}
	if (num_rcands==0){
		return false;
	}
	R=randInt(0,num_rcands);
	for (rp_x=r[R].x;rp_x<(r[R].x+r[R].w);rp_x++){
		for (rp_y=r[R].y;rp_y<(r[R].y+r[R].h);rp_y++){
			mx=r[R].x;
			my=r[R].y;
			map[mx][my]=0;
		}
	}
	return true;
}

bool doesroomfit(int x,int y,int w,int h) {
	int r_x;
	int r_y;
	for (r_x=(x-1);r_x<x+(w+1);r_x++){
		for (r_y=(y-1);r_y<y+(h+1);r_y++){
			if (map[r_x][r_y]==0){
				if (w>=h) {
					max_w--;
				}
				else {
					max_h--;
				}
				return false;
			}
		}
	}
	return true;
}