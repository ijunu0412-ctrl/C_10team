#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

short* main_window();
void window_draw(short flag_window[window_row][window_col]);

short map_data[MAP_SIZE][MAP_SIZE] = { 0 };

void map_main(int* diff)
{
	
	char x1, y1; 
		srand((unsigned)time(NULL));
	int i, j;

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
			map_data[i][j] = ' '; 
	}

	map_data[MAP_SIZE - 2][1] = 'b'; 
	goal_flag();  //골인깃발
	for (i = 0; i < MAP_SIZE; i++)
	{
		map_data[0][i] = '#';            
		map_data[i][0] = '#';            
		map_data[MAP_SIZE - 1][i] = '#'; 
		map_data[i][MAP_SIZE - 1] = '#'; 
	}
		
	switch (*diff) {
	case EASY:
		penalty_flag(*diff); //패널티깃발
		good_flag(*diff);  // 보상깃발
		break;
	case NORMAL:
		penalty_flag(*diff);
		good_flag(*diff);
		break;
	case HARD:
		penalty_flag(*diff);
		good_flag(*diff);
		break;
	}
	

	map_draw();
	window_draw(main_window());

}

void setColor(unsigned short color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}//색 입히기

void map_draw() {
	system("cls");
	COORD baseCur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), baseCur);

	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map_data[i][j] == 'a')
			{
				setColor(4);
				printf("▶");
			}
			else if (map_data[i][j] == 'c')
			{
				setColor(2);
				printf("▶");
			}
			else if (map_data[i][j] == 'g')
			{
				setColor(1);
				printf("▶");
			}
			else if (map_data[i][j] == 'b')
			{
				printf("\u25CF");
			}
			else if (map_data[i][j] == '#')
			{
				printf("■");
			}
			else
				printf(" ");
			setColor(7);
		}
		printf("\n"); 
	}
}

void penalty_flag(int i) {
	int x1, y1, j = 0;
	for (;j < i;j++) {
		y1 = rand() % (MAP_SIZE - 2) + 1;
		x1 = rand() % (MAP_SIZE - 2) + 1;
		if (!(map_data[y1][x1] == 'a' || map_data[y1][x1] == 'b' || map_data[y1][x1] == 'c' || map_data[y1][x1] == 'g'))
			map_data[y1][x1] = 'a';
	}
}

void good_flag(int i) {
	int x1, y1, j = 0;
	for (;j < i;j++) 
	{
		y1 = rand() % (MAP_SIZE - 2) + 1;
		x1 = rand() % (MAP_SIZE - 2) + 1;
		if (!(map_data[y1][x1] == 'a' || map_data[y1][x1] == 'b' || map_data[y1][x1] == 'c' || map_data[y1][x1] == 'g'))
			map_data[y1][x1] = 'c';
	}
}

void goal_flag() 
{
	int x1, y1;
		y1 = rand() % (MAP_SIZE - 2) + 1;
		x1 = rand() % (MAP_SIZE - 2) + 1;
		map_data[y1][x1] = 'g';
	}

void block_object(int *diff)
{
	int x1, y1;
	y1 = rand() % (MAP_SIZE - 2) + 1;
	x1 = rand() % (MAP_SIZE - 2) + 1;
	if (map_data[y1][x1] == ' ')
		map_data[y1][x1] = '#';
}

short* main_window() // 창 생성
{
	int i,j;

	static short flag_window[window_row][window_col] = { 0 };

	for (j = 0;j < window_row;j++)
		for (i = 0;i < window_col;i++)
			flag_window[j][i] = ' ';

	for (i = 0; i < window_col; i++)
	{
		flag_window[0][i] = '*';
		flag_window[window_row-1][i] = '*';
	}

	for (i = 0;i < window_row;i++) {
		flag_window[i][0] = '*';
		flag_window[i][window_col-1] = '*';
	}

	return flag_window;

	}

void window_draw(short flag_window[window_row][window_col]) // 창 구현
{
	int i, j;
	gotoxy(0, MAP_SIZE);
	for (j = 0;j < window_row;j++) {
		for (i = 0;i < window_col;i++)
			printf("%c", flag_window[j][i]);
		printf("\n");
	}
}