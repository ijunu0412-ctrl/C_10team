#include "game.h"

char  flag_window[window_row][window_col];   /* 테두리용으로만 유지 */
short map_data[MAP_SIZE][MAP_SIZE] = { 0 };

int counter1;

/* ──────────────────────────────────────────
   타일 문자 의미
   ' ' = 빈 칸
   '#' = 벽            흰색  ■
   'b' = 플레이어      흰색  ●
   'S' = 시작지점      흰색  ◆  (플레이어가 떠나도 유지)
   'a' = 패널티 깃발   빨강  ▶
   'c' = 보상 깃발     파랑  ▶
   'g' = 골 깃발       노랑  ▶
────────────────────────────────────────── */

/* ── 오브젝트 한 칸 출력 (색상 포함) ─────── */
void draw_tile(int tile) {
    switch (tile) {
    case '#': printf("\033[37m■\033[0m ");  break;
    case 'b': printf("● ");                 break;
    case 'S': printf("\033[97m◆\033[0m ");  break;
    case 'a': printf("\033[31m▶\033[0m ");  break;
    case 'c': printf("\033[34m▶\033[0m ");  break;
    case 'g': printf("\033[33m▶\033[0m ");  break;
    default:  printf("  ");                  break;
    }
}

/* ── 빈 칸 랜덤 위치 반환 ────────────────── */
static void rand_empty(int* rx, int* ry) {
    int x, y;
    do {
        x = 1 + rand() % (MAP_SIZE - 2);
        y = 1 + rand() % (MAP_SIZE - 2);
    } while (map_data[y][x] != ' ');
    *rx = x;
    *ry = y;
}

/* ── 깃발 배치 ───────────────────────────── */
void penalty_flag(int diff) {
    int count = (diff == EASY) ? 3 : (diff == NORMAL) ? 5 : 8;
    int x, y, i;
    for (i = 0; i < count; i++) { rand_empty(&x, &y); map_data[y][x] = 'a'; }
}

void good_flag(int diff) {
    int x, y, i;
    (void)diff;
    for (i = 0; i < 2; i++) { rand_empty(&x, &y); map_data[y][x] = 'c'; }
}

void goal_flag() {
    int x, y;
    do {
        x = 1 + rand() % (MAP_SIZE - 2);
        y = 1 + rand() % (MAP_SIZE / 2);
    } while (map_data[y][x] != ' ');
    map_data[y][x] = 'g';
}

/* ── 맵 전체 그리기 ──────────────────────── */
void map_draw() {
    int i, j;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    system("cls");
    for (j = 0; j < MAP_SIZE; j++) {
        for (i = 0; i < MAP_SIZE; i++) {
            gotoxy(i * 2, j);
            draw_tile(map_data[j][i]);
        }
    }
}

/* ── 맵 초기화 ───────────────────────────── */
void map_main(int* diff)
{
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
        map_data[0][i] = '#';
        map_data[i][0] = '#';
        map_data[MAP_SIZE - 1][i] = '#';
        map_data[i][MAP_SIZE - 1] = '#';
    }

    map_data[py][px] = 'b';

    map_draw();
    main_window();
    window_draw();
}

/* ── 정보창: flag_window는 테두리(*) 전용으로만 사용 ─ */
void main_window()
{
    int i, j;
    for (j = 0; j < window_row; j++)
        for (i = 0; i < window_col; i++)
            flag_window[j][i] = (j == 0 || j == window_row - 1 ||
                i == 0 || i == window_col - 1) ? '*' : ' ';
}

/* ── 정보창 출력: 테두리는 flag_window, 내용은 직접 printf ── */
void window_draw()
{
    int i, j;

    /* 1행~(window_row-1)행: 테두리만 gotoxy로 찍기 */
    for (j = 0; j < window_row; j++) {
        gotoxy(0, MAP_SIZE + j);
        /* 왼쪽 테두리 */
        printf("%c", flag_window[j][0]);

        if (j == 0 || j == window_row - 1) {
            /* 상단/하단 테두리 행 전체 */
            for (i = 1; i < window_col - 1; i++)
                printf("*");
        }
        else if (j == 1) {
            /* 범례 행: ANSI 색상 포함 직접 출력 */
            printf(" \033[31m▶\033[0m:패널티  "
                "\033[34m▶\033[0m:보상  "
                "\033[33m▶\033[0m:골  "
                "\033[97m◆\033[0m:시작");
            /* 나머지 공백 채우기 */
            gotoxy(window_col - 1, MAP_SIZE + j);
        }
        else if (j == 2) {
            /* 난이도 표시 행 */
            const char* diff_str =
                (*difficulty == EASY) ? " 난이도: EASY  " :
                (*difficulty == NORMAL) ? " 난이도: NORMAL" :
                " 난이도: HARD  ";
            printf("%s", diff_str);
            gotoxy(window_col - 1, MAP_SIZE + j);
        }
        else {
            /* 빈 행: 공백만 */
            for (i = 1; i < window_col - 1; i++)
                printf(" ");
        }

        /* 오른쪽 테두리 */
        gotoxy(window_col - 1, MAP_SIZE + j);
        printf("%c", flag_window[j][window_col - 1]);
    }
}

void counter(int* diff)
{
    if (counter1 == 0)
    {
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        system("cls");

        printf("\n");
        printf("  =====================================\n");
        printf("             GAME OVERㅠㅠ         \n");
        printf("  =====================================\n");
        printf("\n");
        printf("  계속하시겠습니까?\n");
        printf("\n");

        int sel = 0;   /* 0: 난이도 재도전, 1: 게임 종료 */
        const char* opts[] = { "재도전", "게임 종료" };

        /* 선택지가 그려질 행: \n 개수로 결정
           \n(1) + 헤더4줄 + \n(1) + 계속하시겠습니까\n(1) + \n(1) = 8행 */
        const int MENU_ROW = 8;

        while (1) {
            /* ★ 항상 같은 위치에서 덮어쓰기 */
            gotoxy(0, MENU_ROW);
            for (int k = 0; k < 2; k++) {
                printf(sel == k ? " > %-25s\n" : "   %-25s\n", opts[k]);
            }

            int key = _getch();
            if (key == 0 || key == 224) {
                key = _getch();
                if (key == UP)   sel = (sel == 0) ? 1 : 0;
                if (key == DOWN) sel = (sel == 1) ? 0 : 1;
            }
            else if (key == ENTER) {
                break;
            }
        }
        if (sel == 0) {
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            counter1 = 4;
            map_main(difficulty);
        }
        else {
            system("cls");
            printf("\n  게임을 종료합니다.\n");
            exit(0);
        }
    }
    switch (*diff)
    {
    case EASY:
        gotoxy(MAP_SIZE * 2, 0);
        printf("이동횟수: %d ", counter1);
        break;
    case NORMAL:
        gotoxy(MAP_SIZE * 2, 0);
        printf("이동횟수: % d ", counter1);
        break;
    case HARD:
        gotoxy(MAP_SIZE * 2, 0);
        printf("이동횟수: %d ", counter1);
        break;
    }
    return 0;
}


void counter_level(int* diff) {
    switch (*diff) {
    case EASY:counter1 = 50; break;
    case NORMAL:counter1 = 40; break;
    case HARD:counter1 = 30; break;
    }
}