#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAP_SIZE 20

#define EMPTY  0
#define WALL   1
#define START  2
#define FLAG   3
#define PLAYER 99

#define STATE_PLAY  1
#define STATE_PAUSE 2

#define UP    72
#define DOWN  80
#define LEFT  75
#define RIGHT 77
#define ENTER 13

#define EASY   1
#define NORMAL 2
#define HARD   3

#define window_row  7
#define window_col  80

/* ── 전역 변수 외부 참조 ─────────────────── */
extern int   gamestate;
extern int   px;
extern int   py;
extern int   previoustile;
extern int   game_difficulty;
extern int*  difficulty;

/* ★ 헤더에서 정의(int)가 아닌 선언(extern)만 — 실제 정의는 map.c */
extern int   counter1;
extern int   flagcounter;

extern short map_data[MAP_SIZE][MAP_SIZE];

extern DWORD msg_start_time;
extern int   msg_active;

extern char  flag_window[window_row][window_col];

/* ── 함수 선언 ───────────────────────────── */
void settitle();
void map_main(int* diff);
void main_move();
void play_transition();

int  mainMenu();
int  selectDifficulty();
void showInstructions();

void counter(int* diff);
void counter_level(int* diff);

void map_draw();
void draw_tile(int tile);
void penalty_flag(int diff);
void good_flag(int diff);
void goal_flag();

void gotoxy(int x, int y);
void main_window();
void window_draw();
void update_message_timer();

#endif
