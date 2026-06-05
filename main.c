#include "game.h"

int main(void) {
    settitle();
    map_main(difficulty);

    while (1) {
        main_move();

        // 실시간으로 타이머 경과 여부를 검사하여 1초 뒤 대사를 자동으로 지웁니다.
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