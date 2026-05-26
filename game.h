#ifndef GAME_H
#define GAME_H
#define MAP_SIZE 15

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

extern int gamestate;
extern int px;
extern int py;
extern int previoustile;

void settitle();
void mapmain();
void main_move();

#endif