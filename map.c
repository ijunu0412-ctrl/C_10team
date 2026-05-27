#include "game.h"

short map_data[MAP_SIZE][MAP_SIZE] = { 0 };

void map()
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

		for (i = 0; i < MAP_SIZE; i++)
		{
			map_data[0][i] = '#';            
			map_data[i][0] = '#';            
			map_data[MAP_SIZE - 1][i] = '#'; 
			map_data[i][MAP_SIZE - 1] = '#'; 
		}
		

	for (i = 0; i < 7; i++) {
		y1 = rand() % (MAP_SIZE - 2) + 1;
		x1 = rand() % (MAP_SIZE - 2) + 1;
		if (map_data[y1][x1] == 'a' || map_data[y1][x1] == 'b')
			i--;
		else
			map_data[y1][x1] = 'a'; 
	}

	map_draw();
}
void map_draw() {
	system("cls");
	COORD baseCur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), baseCur);

	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map_data[i][j] == 'a')
				printf("▶"); 
			else if (map_data[i][j] == 'b')
				printf("\u25CF"); 
			else if (map_data[i][j] == '#')
				printf("■"); // 2칸 크기 벽 통일
			else
				printf(" "); 
		}
		printf("\n"); 
	}
}