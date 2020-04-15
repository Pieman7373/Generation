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
