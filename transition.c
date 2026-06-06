#include "game.h"



void play_transition() {
    char symbols[] = { '@', '#', '$', '%', '&' };
    int x, y;
    int max_sum = (MAP_SIZE - 1) + (MAP_SIZE - 1);  /* = 38 */

    /* ── 1단계: 심볼로 화면 채우기── */
    for (int sum = 0; sum <= max_sum; sum++) {
        for (y = 0; y < MAP_SIZE; y++) {
            x = sum - y;
            if (x >= 0 && x < MAP_SIZE) {
                gotoxy(x * 2, y);
                printf("%c ", symbols[rand() % 5]);
            }
        }
        Sleep(30);
    }

    Sleep(420);

    /* ── 2단계: 맵 복원  ── */
    for (int sum = 0; sum <= max_sum; sum++) {
        for (y = 0; y < MAP_SIZE; y++) {
            x = sum - y;
            if (x >= 0 && x < MAP_SIZE) {
                gotoxy(x * 2, y);
                switch (map_data[y][x]) {
                case '#': printf("\033[37m■\033[0m ");  break;  /* 벽: 흰색  */
                case 'b': printf("● ");                 break;  /* 플레이어  */
                case 'S': printf("\033[97m◆\033[0m ");  break;  /* 시작: 밝은 흰색 */
                case 'a': printf("\033[35m▶\033[0m ");  break;  /* 패널티: 보라 */
                case 'c': printf("\033[35m▶\033[0m ");  break;  /* 보상: 보라   */
                case 'g': printf("\033[33m▶\033[0m ");  break;  /* 골: 노랑     */
                default:  printf("  ");                  break;
                }
            }
        }
        Sleep(35);
    }

    Sleep(300);

    window_draw();
}
