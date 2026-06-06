#include "game.h"

void auto_diff(int previoustile);

int px = 1, py = MAP_SIZE - 2;
int gamestate = STATE_PLAY;
int previoustile = 0;

DWORD msg_start_time = 0;
int   msg_active     = 0;

/* 시작 지점 좌표 (맵 리셋 시에도 항상 고정) */
#define START_X 1
#define START_Y (MAP_SIZE - 2)

/* ── 커서 이동 ───────────────────────────── */
void gotoxy(int x, int y) {
    COORD cur = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

/* ── 걷기 효과음 ─────────────────────────── */
static void playwalksound() {
    Beep(500, 7);
}

/* ── 플레이어를 특정 위치로 이동하고 화면 갱신 ─
   이전 위치는 원래 타일(비어있으면 ' ', 시작이면 'S')로 복원 */
static void move_player_to(int new_x, int new_y, int restore_tile) {
    /* 현재 위치 복원 */
    map_data[py][px] = restore_tile;
    gotoxy(px * 2, py);
    draw_tile(restore_tile);

    /* 새 위치로 이동 */
    px = new_x;
    py = new_y;
    map_data[py][px] = 'b';
    gotoxy(px * 2, py);
    printf("●");
}

/* ── 플레이어 이동 ───────────────────────── */
void main_move() {
    if (!_kbhit()) return;

    int input = _getch();
    int dx = 0, dy = 0;

    if (input == 0 || input == 224) {
        input = _getch();
        switch (input) {
        case UP:    dy = -1; break;
        case DOWN:  dy =  1; break;
        case LEFT:  dx = -1; break;
        case RIGHT: dx =  1; break;
        default: return;
        }
    }
    else if (input == 27) {
        gamestate = STATE_PAUSE;
        return;
    }
    else {
        switch (input) {
        case 'w': case 'W': dy = -1; break;
        case 's': case 'S': dy =  1; break;
        case 'a': case 'A': dx = -1; break;
        case 'd': case 'D': dx =  1; break;
        default: return;
        }
    }

    int nextpx = px + dx;
    int nextpy = py + dy;

    if (nextpx < 0 || nextpx >= MAP_SIZE || nextpy < 0 || nextpy >= MAP_SIZE) return;
    if (map_data[nextpy][nextpx] == '#') return;

    playwalksound();

    /* 현재 칸을 떠날 때 복원할 타일 결정:
       시작 위치라면 'S', 그 외엔 ' ' */
    int restore = (px == START_X && py == START_Y) ? 'S' : ' ';

    previoustile = map_data[nextpy][nextpx];

    /* 이전 위치 복원 후 새 위치로 이동 */
    map_data[py][px] = restore;
    gotoxy(px * 2, py);
    draw_tile(restore);

    map_data[nextpy][nextpx] = 'b';
    gotoxy(nextpx * 2, nextpy);
    printf("●");

    px = nextpx;
    py = nextpy;

    /* 타일 이벤트 처리 (내부에서 px/py 변경 가능) */
    auto_diff(previoustile);
}

/* ── 메시지 표시 헬퍼 ────────────────────── */
#define SHOW_MSG(str) do { \
    gotoxy(2, MAP_SIZE + 2); \
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　"); \
    gotoxy(2, MAP_SIZE + 2); \
    printf(str); \
    msg_start_time = GetTickCount(); \
    msg_active = 1; \
} while(0)

/* ── 플레이어를 시작 위치로 복귀 ────────────
   ★ 시작 위치의 'S' 타일을 지우지 않고 플레이어만 올림 */
static void return_to_start() {
    /* 현재 위치 비우기 (시작점이면 'S' 복원, 아니면 ' ') */
    int restore = (px == START_X && py == START_Y) ? 'S' : ' ';
    map_data[py][px] = restore;
    gotoxy(px * 2, py);
    draw_tile(restore);

    /* 시작 위치로 이동 */
    px = START_X;
    py = START_Y;
    map_data[py][px] = 'b';
    gotoxy(px * 2, py);
    printf("●");
}

/* ── 타일 이벤트 처리 ────────────────────── */
void auto_diff(int tile)
{
    const char* penalty_ment[] = {
        "설계자: 함정이었지. 처음으로 돌아가라!",
        "설계자: 호호, 이 함정을 밟다니!",
        "설계자: 아직 멀었군. 다시 시작이야!",
        "설계자: 안타깝군... 출발점으로!"
    };
    int rand_idx = rand() % 4;

    switch (tile) {
    case 'a':   /* 패널티 깃발 → 시작 위치로 복귀 */
        SHOW_MSG(penalty_ment[rand_idx]);
        return_to_start();
        break;

    case 'g':   /* 골 깃발 */
        if (*difficulty <= HARD) {
            /* transition이 ~3000ms 동안 실행되면서 메시지도 같이 표시 */
            gotoxy(2, MAP_SIZE + 2);
            printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
            gotoxy(2, MAP_SIZE + 2);
            printf("과제 제출에 성공하였습니다!");
            play_transition();          /* ← 내부에서 3000ms 소요 */
            (*difficulty)++;
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            map_main(difficulty);
        }
        else {
            /* ── Hard 클리어 선택지 ── */
            play_transition();
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            system("cls");

            printf("\n");
            printf("  =====================================\n");
            printf("          모든 과제 제출 성공!          \n");
            printf("        성공적으로 졸업했습니다!        \n");
            printf("  =====================================\n");
            printf("\n");
            printf("  계속하시겠습니까?\n");
            printf("\n");

            int sel = 0;   /* 0: Hard 재도전, 1: 게임 종료 */
            const char* opts[] = { "Hard 난이도 재도전", "게임 종료" };

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
                /* Hard 난이도 유지하고 맵 재생성 */
                *difficulty = HARD;
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                map_main(difficulty);
            }
            else {
                system("cls");
                printf("\n  게임을 종료합니다.\n");
                exit(0);
            }
        }
        break;

    case 'c':   /* 보상 깃발 → 난이도 한 단계 하향 */
        SHOW_MSG("설계자: 보상 깃발이군. 난이도를 한 단계 낮춰주지!");
        if (*difficulty > EASY)
            (*difficulty)--;
        break;
    }
}

#undef SHOW_MSG

/* ── 메시지 자동 소거 (1초 후) ──────────── */
void update_message_timer() {
    if (msg_active && (GetTickCount() - msg_start_time >= 1000)) {
        gotoxy(2, MAP_SIZE + 2);
        printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
        msg_active = 0;
    }
}
