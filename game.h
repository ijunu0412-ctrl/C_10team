#define GAME_H
#define MAP_SIZE 20

#define EMPTY 0
#define WALL 1
#define START 2
#define FLAG 3
#define PLAYER 99

#define STATE_PLAY 1
#define STATE_PAUSE 2

#define SHAPE_PLAYER "\u25CF"
#define SHAPE_START "\u25C6"
#define SHAPE_EMPTY "  "

#define UP 72
#define DOWN 80
#define ENTER 13

#define EASY 1
#define NORMAL 2
#define HARD 3


extern int gamestate;
extern int px;
extern int py;
extern int previoustile;

extern short map_data[][MAP_SIZE];

void settitle();
void map_main(int* difficulty);
void main_move();

int mainMenu();
int selectDifficulty();
void showInstructions();
void map_draw();
void penalty_flag(int i);
void good_flag(int i);
void goal_flag();
void gotoxy(int x, int y);

#include <stdio.h>
#include <conio.h>   
#include<windows.h>
#include <stdlib.h>
#include<time.h>