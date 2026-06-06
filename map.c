#include "game.h"

char  flag_window[window_row][window_col];
short map_data[MAP_SIZE][MAP_SIZE] = { 0 };

/* ★ 전역 변수 실제 정의 (extern 선언은 game.h) */
int counter1  = 0;
int flagcounter = 0;

/* ──────────────────────────────────────────
   타일 문자 의미
   ' ' = 빈 칸
   '#' = 벽            흰색  ■
   'b' = 플레이어            ●
   'S' = 시작지점      밝은흰 ◆
   'a' = 패널티 깃발   보라  ▶
   'c' = 보상 깃발     보라  ▶
   'g' = 골 깃발       노랑  ▶
────────────────────────────────────────── */

void draw_tile(int tile) {
    switch (tile) {
    case '#': printf("\033[37m■\033[0m ");  break;
    case 'b': printf("● ");                 break;
    case 'S': printf("\033[97m◆\033[0m ");  break;
    case 'a': printf("\033[35m▶\033[0m ");  break;  /* 보라: 패널티 */
    case 'c': printf("\033[35m▶\033[0m ");  break;  /* 보라: 보상   */
    case 'g': printf("\033[33m▶\033[0m ");  break;  /* 노랑: 골     */
    default:  printf("  ");                  break;
    }
}

static void rand_empty(int* rx, int* ry) {
    int x, y;
    do {
        x = 1 + rand() % (MAP_SIZE - 2);
        y = 1 + rand() % (MAP_SIZE - 2);
    } while (map_data[y][x] != ' ');
    *rx = x;
    *ry = y;
}

void penalty_flag(int diff) {
    int count = (diff == EASY) ? 3 : (diff == NORMAL) ? 5 : 8;
    int x, y, i;
    for (i = 0; i < count; i++) { rand_empty(&x, &y); map_data[y][x] = 'a'; }
}

void good_flag(int diff) {
    int x, y, i;
    (void)diff;
    for (i = 0; i < 4; i++) { rand_empty(&x, &y); map_data[y][x] = 'c'; }
}

void goal_flag() {
    int x, y;
    do {
        x = 1 + rand() % (MAP_SIZE - 2);
        y = 1 + rand() % (MAP_SIZE / 2);
    } while (map_data[y][x] != ' ');
    map_data[y][x] = 'g';
}

void map_draw() {
    int i, j;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    system("cls");
    for (j = 0; j < MAP_SIZE; j++)
        for (i = 0; i < MAP_SIZE; i++) {
            gotoxy(i * 2, j);
            draw_tile(map_data[j][i]);
        }
}

void map_main(int* diff) {
    int i, j;

    srand((unsigned)time(NULL));

    for (i = 0; i < MAP_SIZE; i++)
        for (j = 0; j < MAP_SIZE; j++)
            map_data[j][i] = ' ';

    px = 1;
    py = MAP_SIZE - 2;
    map_data[py][px] = 'S';

    penalty_flag(*diff);
    good_flag(*diff);
    goal_flag();

    for (i = 0; i < MAP_SIZE; i++) {
        map_data[0][i]          = '#';
        map_data[i][0]          = '#';
        map_data[MAP_SIZE-1][i] = '#';
        map_data[i][MAP_SIZE-1] = '#';
    }

    map_data[py][px] = 'b';

    map_draw();
    main_window();
    window_draw();
}

void main_window() {
    int i, j;
    for (j = 0; j < window_row; j++)
        for (i = 0; i < window_col; i++)
            flag_window[j][i] = (j == 0 || j == window_row-1 ||
                                  i == 0 || i == window_col-1) ? '*' : ' ';
}

void window_draw() {
    int i, j;
    for (j = 0; j < window_row; j++) {
        gotoxy(0, MAP_SIZE + j);
        printf("%c", flag_window[j][0]);

        if (j == 0 || j == window_row - 1) {
            for (i = 1; i < window_col - 1; i++) printf("*");
        }
        else if (j == 1) {
            printf(" \033[35m▶\033[0m:패널티  "
                   "\033[35m▶\033[0m:보상  "
                   "\033[33m▶\033[0m:골  "
                   "\033[97m◆\033[0m:시작");
            gotoxy(window_col - 1, MAP_SIZE + j);
        }
        else if (j == 2) {
            const char* diff_str =
                (*difficulty == EASY)   ? " 난이도: EASY  " :
                (*difficulty == NORMAL) ? " 난이도: NORMAL" :
                                          " 난이도: HARD  ";
            printf("%s", diff_str);
            gotoxy(window_col - 1, MAP_SIZE + j);
        }
        else {
            for (i = 1; i < window_col - 1; i++) printf(" ");
        }

        gotoxy(window_col - 1, MAP_SIZE + j);
        printf("%c", flag_window[j][window_col - 1]);
    }
}

/* ── 이동횟수 / 학점 표시 + 게임오버 판정 ── */
void counter(int* diff) {
    /* 이동횟수 표시 (맵 오른쪽, 0행) */
    gotoxy(MAP_SIZE * 2, 0);
    printf("이동횟수: %3d ", counter1);

    /* ★ flagcounter 표시 (이동횟수 바로 아래, 1행) */
    gotoxy(MAP_SIZE * 2, 1);
    printf("학점조각: %3d ", flagcounter);

    /* 이동횟수가 0 이하면 게임오버 */
    if (counter1 > 0) return;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");

    printf("\n");
    printf("  =====================================\n");
    printf("             GAME OVERㅠㅠ             \n");
    printf("  =====================================\n");
    printf("\n");
    printf("  계속하시겠습니까?\n");
    printf("\n");

    int sel = 0;
    const char* opts[] = { "재도전", "게임 종료" };
    const int MENU_ROW = 8;

    while (1) {
        gotoxy(0, MENU_ROW);
        for (int k = 0; k < 2; k++)
            printf(sel == k ? " > %-25s\n" : "   %-25s\n", opts[k]);

        int key = _getch();
        if (key == 0 || key == 224) {
            key = _getch();
            if (key == UP)   sel = (sel == 0) ? 1 : 0;
            if (key == DOWN) sel = (sel == 1) ? 0 : 1;
        }
        else if (key == ENTER) break;
    }

    if (sel == 0) {
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        counter_level(diff);
        map_main(diff);
    }
    else {
        system("cls");
        printf("\n  게임을 종료합니다.\n");
        exit(0);
    }
}

void counter_level(int* diff) {
    switch (*diff) {
    case EASY:   counter1 = 50; break;
    case NORMAL: counter1 = 40; break;
    case HARD:   counter1 = 30; break;
    }
}
