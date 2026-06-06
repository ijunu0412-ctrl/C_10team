#include "game.h"


int menu_selected = 0;       // 메인 메뉴의 커서 위치 (0: 시작, 1: 방법, 2: 종료)
int game_difficulty = 1;     // 실제 선택된 게임 난이도 (1: 쉬움, 2: 보통, 3: 어려움)
int* difficulty = &game_difficulty; // main.c에서 참조할 포인터

void settitle() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    system("cls");

    int menuChoice;


    while (1) {
        menuChoice = mainMenu();

        if (menuChoice == 0) {

            game_difficulty = selectDifficulty();
            return;
        }
        else if (menuChoice == 1) {
            showInstructions();
        }
        else if (menuChoice == 2) {
            system("cls");
            printf("\n게임을 종료합니다.\n");
            exit(0);
        }
    }
}


int mainMenu() {
    int key;
    const char* menuDisplay[] = {
        "=====================================",
        "                                     ",
        "        대학생 과제 시뮬레이터       ",
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
            if (i >= 5) {
                int menuIndex = i - 5;

                if (menu_selected == menuIndex) {
                    printf(" >%s\n", menuDisplay[i]);
                }
                else {
                    printf("  %s\n", menuDisplay[i]);
                }
            }
            else {
                printf("%s\n", menuDisplay[i]);
            }
        }

        key = _getch();
        if (key == 0 || key == 224) {
            key = _getch();
            if (key == UP) {
                menu_selected = (menu_selected == 0) ? 2 : menu_selected - 1;
            }
            else if (key == DOWN) {
                menu_selected = (menu_selected == 2) ? 0 : menu_selected + 1;
            }
        }
		else if (key == 'w' || key == 'W') {
			menu_selected = (menu_selected == 0) ? 2 : menu_selected - 1;
		}
		else if (key == 's' || key == 'S') {
			menu_selected = (menu_selected == 2) ? 0 : menu_selected + 1;
		}
        else if (key == ENTER) {
            return menu_selected;
        }
    }
}


int selectDifficulty() {
    int key;
    int selected = 0;

    const char* diffDisplay[] = {
        "=====================================",
        "       수강할 과목을 선택하세요      ",
        "=====================================",
        "  [1] Easy: 꿀교양",
        "  [2] Normal: 전공 기초",
        "  [3] Hard: 전공 심화"
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
        else if (key == 'w' || key == 'W') {
            selected = (selected == 0) ? 2 : selected - 1;
        }
        else if (key == 's' || key == 'S') {
            selected = (selected == 2) ? 0 : selected + 1;
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
        "1.조작키:화살표                     ",
        "2.푸른 깃발은 마감일을 늘려주고, 후속 강의 수강권 조각이 제공됩니다.",
        "3.붉은 깃발은 마감일을 차감하고, 후속 강의 수강권 조각을 없앱니다.",
        "4.노란 깃발은 과제 제출입니다. 모든 수업의 과제를 제출하는 것이 목표입니다.",
        "5.행운을 빌어요!",                          
        "=====================================",
        " 아무 키나 누르면 메인 메뉴로 돌아갑니다."
    };
    int totalLines = sizeof(instructions) / sizeof(instructions[0]);

    for (int i = 0; i < totalLines; i++) {
        printf("%s\n", instructions[i]);
    }

    _getch();
}