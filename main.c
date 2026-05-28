#include"game.h"

int main(void) {
    extern int* difficulty;
	settitle();
    map_main(difficulty);
   
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
    return 0;
	}