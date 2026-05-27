#include "game.h"

void settitle() {

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    system("cls"); //구글에서 커서 투명하게 하는 법<<이거 쳐서 복붙함
    int menuChoice;
    int difficulty = EASY; // 기본 난이도 초기화

    while (1) {
        menuChoice = mainMenu(); // 메인 메뉴 실행

        if (menuChoice == 0) {
            difficulty = selectDifficulty(); // 난이도 선택 화면으로 이동
            
            return;
        }
        else if (menuChoice == 1) {
            showInstructions(); // 게임 설명 화면
        }
        else if (menuChoice == 2) {
            system("cls");
            printf("\n게임을 종료합니다.\n"); // 종료
            exit(0);
        }
    }
}

// 메인타이틀
int mainMenu() {
    int key;
    int selected = 0;

    const char* menuDisplay[] = {
        "=====================================",
        "        C PROGRAMMING PROJECT        ",
        "                                     ",
        "=====================================",
        "  1. 게임 시작 ",
        "  2. 게임 방법 ",
        "  3. 게임 종료 "
    };
    int totalLines = sizeof(menuDisplay) / sizeof(menuDisplay[0]);

    while (1) {
        system("cls");
        printf("\n");

        for (int i = 0; i < totalLines; i++) {
            if (i >= 4) {
                int menuIndex = i - 4;
                if (selected == menuIndex) {
                    printf(" >%s\n", menuDisplay[i]); // 선택된 메뉴 앞에 '>' 표시
                }
                else {
                    printf("  %s\n", menuDisplay[i]);
                }
            }
            else {
                // 타이틀 텍스트 출력
                printf("%s\n", menuDisplay[i]);
            }
        }

        key = _getch();
        if (key == 0 || key == 224) {
            key = _getch();
            if (key == UP) {
                selected = (selected == 0) ? 2 : selected - 1;
            }
            else if (key == DOWN) {
                selected = (selected == 2) ? 0 : selected + 1;
            }
        }
        else if (key == ENTER) {
            return selected;
        }
    }
}

int selectDifficulty() {
    int key;
    int selected = 0;

    const char* diffDisplay[] = {
        "=====================================",
        "          SELECT DIFFICULTY          ",
        "=====================================",
        "  [1] (Easy)",
        "  [2] (Normal)",
        "  [3] (Hard)"
    };
    int totalLines = sizeof(diffDisplay) / sizeof(diffDisplay[0]);

    while (1) {
        system("cls");
        printf("\n");

        for (int i = 0; i < totalLines; i++) {
            if (i >= 3) {
                int diffIndex = i - 3;
                if (selected == diffIndex) {
                    printf(" >%s\n", diffDisplay[i]);
                }
                else {
                    printf("  %s\n", diffDisplay[i]);
                }
            }
            else {
                printf("%s\n", diffDisplay[i]);
            }
        }

        key = _getch();
        if (key == 0 || key == 224) {
            key = _getch();
            if (key == UP) selected = (selected == 0) ? 2 : selected - 1;
            else if (key == DOWN) selected = (selected == 2) ? 0 : selected + 1;
        }
        else if (key == ENTER) {
            return selected + 1;
        }
    }
}

void showInstructions() {
    system("cls");

    const char* instructions[] = {
        "\n=====================================",
        "            HOW TO PLAY              ",
        "=====================================",
        "                                      ",
        "=====================================",
        " 아무 키나 누르면 메인 메뉴로 돌아갑니다."
    };
    int totalLines = sizeof(instructions) / sizeof(instructions[0]);

    for (int i = 0; i < totalLines; i++) {
        printf("%s\n", instructions[i]);
    }

    _getch();
}