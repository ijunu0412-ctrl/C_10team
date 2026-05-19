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
	Beep(500, 15);
}

void main_move(int map[MAP_SIZE][MAP_SIZE]) {
	
	if (!_kbhit()) return;

	int input = _getch();

	if (input == 27) {
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
		if (map[nextpy][nextpx] != WALL) {

			playwalksound();

			map[py][px] = previoustile;
			gotoxy(px, py);

			if (previoustile == START)
				printf("%s", SHAPE_START);
			else
				printf("%s", SHAPE_EMPTY);

			previoustile = map[nextpy][nextpx];

			map[nextpy][nextpx];
			gotoxy(nextpx, nextpy);
			printf("%s", SHAPE_PLAYER);

			px = nextpx;
			py = nextpy;
			
		}
	}
} 




int main() //예시 main함수
{

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo); 
	system("cls"); //구글에서 커서 투명하게 하는 법<<이거 쳐서 복붙함

    int testMap[MAP_SIZE][MAP_SIZE] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,9,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

  
    px = 1;
    py = 1;
    gamestate = 1;      
    previoustile = 2; 

 
    system("cls");
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (testMap[i][j] == 1) printf("##");
            else if (testMap[i][j] == 9) printf("%s", SHAPE_PLAYER);
            else printf("  ");
        }
        printf("\n");
    }

 
    while (1) {
        main_move(testMap);

       
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
    return 0;
}