#include"game.h"

int main(void) {
    extern int* difficulty;
	
    do {
        settitle();
        px = 1, py = MAP_SIZE - 2;
        map_main(difficulty);

        while (*difficulty !=4) {
            counter(difficulty);
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
    } while (1);
    return 0;
	}