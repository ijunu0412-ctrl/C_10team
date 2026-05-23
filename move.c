#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "game.h"


int px, py, gamestate, previoustile, nextpx, nextpy;

void gotoxy(int x, int y) {
	COORD cur = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void playwalksound() {
	Beep(500, 7);
}

void main_move(char map[MAP_SIZE][MAP_SIZE]) {

	if (!_kbhit()) return;

	int input = _getch();

	if (input == 27) {	//esc:27
		gamestate = STATE_PAUSE;
		//MENU
		return;
	}

	if (gamestate == STATE_PAUSE) {
		return;
	}

	int dx = 0, dy = 0;
	switch (input) {
	case 'w':
	case 'W': dy = -1; break;

	case 'a':
	case 'A': dx = -1; break;

	case 's':
	case 'S': dy = 1; break;

	case 'd':
	case 'D': dx = 1; break;

	default: return;
	}

	int nextpx = px + dx;
	int nextpy = py + dy;

	if (nextpx >= 0 && nextpx < MAP_SIZE && nextpy >= 0 && nextpy < MAP_SIZE) {
		if (map[nextpy][nextpx] != '#') {

			playwalksound();

			map[py][px] = previoustile;
			gotoxy(px, py);

			if (previoustile == '#')
				printf("■"); // 벽을 밟았다면 '#' 복구
			else
				printf("  ");

			previoustile = map[nextpy][nextpx];

			gotoxy(nextpx, nextpy);
			printf("%s", SHAPE_PLAYER);

			px = nextpx;
			py = nextpy;

		}
	}
}




void mainmove() //예시 main함수
{
	system("mode con cols=80 lines=30");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
	system("cls"); //구글에서 커서 투명하게 하는 법<<이거 쳐서 복붙함

	system("cls");
	mapmain();

	px = 1;
	py = 1;
	gamestate = 1;
	previoustile = ' ';

	gotoxy(px, py);
	printf("%s", SHAPE_PLAYER);

	while (1) {
		main_move(map_data);


		if (gamestate == STATE_PAUSE) {
			gotoxy(0, MAP_SIZE + 1);
			printf("[PAUSE] 1을 누르면 복귀: ");
			if (_getch() == '1') {
				gamestate = 1;
				gotoxy(0, MAP_SIZE + 1);
				printf("                                       ");
			}
		}
		Sleep(10);
	}
}