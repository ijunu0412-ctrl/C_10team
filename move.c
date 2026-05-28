#include "game.h"

int px = 1, py = MAP_SIZE - 2, gamestate = 1, previoustile = 2, nextpx, nextpy;
extern int* difficulty;

void gotoxy(int x, int y) {
	COORD cur = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void playwalksound() {
	Beep(500, 7);
}

void main_move(short map[MAP_SIZE][MAP_SIZE]) {
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
			previoustile = 0;
			map[py][px] = previoustile;
			gotoxy(px, py);
			printf(" ");

			previoustile = map[nextpy][nextpx];
			gotoxy(nextpx, nextpy);
			printf("\u25CF");

			switch (previoustile) {
			case 'a':
				gotoxy(0, MAP_SIZE + 1);
				printf("패널티 깃발입니다.               ");
				break;
			case 'g':
				if (*difficulty != HARD){
					gotoxy(0, MAP_SIZE + 1);
					printf("골인~~~~~,3초후다음단계     ");
					Sleep(3000);
					(*difficulty)++;
					map_main(difficulty);
					break;
				}
				else{
					gotoxy(0, MAP_SIZE + 1);
					printf("HARD난이도를 클리어하셨습니다!");
					(*difficulty)++;
					break;
				}
			case 'c':
				gotoxy(0, MAP_SIZE + 1);
				printf("보상 깃발입니다.            ");
				break;
			}


			if (previoustile == 'g' && *difficulty !=4)
			{
				px = 1;
				py = MAP_SIZE - 2;
			}
			else {
				px = nextpx;
				py = nextpy;
			}

		}
	}
}



