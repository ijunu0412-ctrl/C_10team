#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include "game.h"

/*char map_data[MAP_SIZE][MAP_SIZE] = {0};

void map();
void mapmain()
{
	map();
}

void map()
{

	char x1, y1;
	srand((unsigned)time(NULL));
	int i, j;

	COORD baseCur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), baseCur);

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
			map_data[i][j] = ' ';
	}
	map_data[MAP_SIZE-2][1] = 'b';
	for (i = 0; i < MAP_SIZE; i++)
	{
		map_data[0][i] = '#';
		map_data[i][0] = '#';
		map_data[MAP_SIZE-1][i] = '#';
		map_data[i][MAP_SIZE-1] = '#';
	}

	for (i = 0; i < 7; i++) {
		y1 = rand() % (MAP_SIZE - 2) + 1;
		x1 = rand() % (MAP_SIZE-2) + 1;
		
		if (map_data[y1][x1] == 'a' || map_data[y1][x1] == 'b')
			i--;
		else
			map_data[y1][x1] = 'a';
	}

	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map_data[i][j] == 'a') {
				printf("▶"); 
			}
			else if (map_data[i][j] == 'b') {
				printf("◆"); 
			}
			else if (map_data[i][j] == '#') {
				printf("■");
				
				
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
}
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <windows.h>
#include "game.h"

char map_data[MAP_SIZE][MAP_SIZE] = { 0 }; [cite:1]

void map();
void map_draw(); // 맵을 화면에 정렬해서 그리는 함수 추가

void mapmain()
{
	map(); [cite:1]
}

void map()
{
	char x1, y1; [cite:1]
		srand((unsigned)time(NULL));
	int i, j;

	// 1. 전체 공백 초기화
	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
			map_data[i][j] = ' '; [cite:1]
	}

	// 2. 목적지 배치
	map_data[MAP_SIZE - 2][1] = 'b'; [cite:1]

		// 3. 테두리 벽 정확하게 생성 ([세로][가로] 축 일치)
		for (i = 0; i < MAP_SIZE; i++)
		{
			map_data[0][i] = '#';            // 위쪽 벽[cite: 1]
			map_data[i][0] = '#';            // 왼쪽 벽[cite: 1]
			map_data[MAP_SIZE - 1][i] = '#'; // 아래쪽 벽[cite: 1]
			map_data[i][MAP_SIZE - 1] = '#'; // 오른쪽 벽[cite: 1]
		}

	// 4. 안쪽에만 안전하게 아이템 생성 (축 오류 교정)
	for (i = 0; i < 7; i++) {
		y1 = rand() % (MAP_SIZE - 2) + 1;
		x1 = rand() % (MAP_SIZE - 2) + 1;
		if (map_data[y1][x1] == 'a' || map_data[y1][x1] == 'b')
			i--;
		else
			map_data[y1][x1] = 'a'; [cite:1]
	}

	// 최초 1회 화면에 맵 그리기
	map_draw();
}

// 💡 [핵심] 화면 깨짐과 밀림을 완벽하게 방지하는 정렬 출력 함수
void map_draw() {
	// 화면 커서를 좌측 최상단 (0, 0)으로 강제 고정하여 잔상과 밀림 원천 차단
	COORD baseCur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), baseCur);

	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map_data[i][j] == 'a')
				printf("▶"); [cite:1]
			else if (map_data[i][j] == 'b')
				printf("◆"); [cite:1]
			else if (map_data[i][j] == '#')
				printf("■"); // 2칸 크기 벽 통일
			else
				printf("  "); // 공백 2칸 통일
		}
		printf("\n"); [cite:1]
	}
}