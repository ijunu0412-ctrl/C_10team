#include "game.h"

int main(void) {
    settitle();
    map_main(difficulty);
    counter_level(difficulty);

    while (1) {
        main_move();
        counter(difficulty);
        
        update_message_timer();

        if (gamestate == STATE_PAUSE) {
            gotoxy(0, MAP_SIZE + window_row + 1);
            printf("[PAUSE] 1을 누르면 복귀: ");
            if (_getch() == '1') {
                gamestate = STATE_PLAY;
                gotoxy(0, MAP_SIZE + window_row + 1);
                printf("                                       ");
            }
        }
        Sleep(10);
    }
    return 0;
}