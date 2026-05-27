#include"game.h"

int main(void) {
    extern int* difficulty;
	settitle();
    switch (*difficulty) {
    case 1:
        map();//난이도 쉬움
        break;
    case 2:
        map();//난이도 보통
        break;
    case 3:
        map();//난이도 어려움
        break;
        //map()함수에 정수 매개변수를 추가해서 switch문으로 케이스를 나눠주면 될 듯 합니다. 
    }
	
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