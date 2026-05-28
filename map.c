#include "game.h"

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
}
void map_draw() {
	system("cls");
	COORD baseCur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), baseCur);

	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map_data[i][j] == 'a' || map_data[i][j] == 'c' || map_data[i][j] == 'g')
				printf("▶"); 
			else if (map_data[i][j] == 'b')
				printf("\u25CF"); 
			else if (map_data[i][j] == '#')
				printf("■"); 
			else
				printf(" "); 
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
	for (;j < i;j++) {
		y1 = rand() % (MAP_SIZE - 2) + 1;
		x1 = rand() % (MAP_SIZE - 2) + 1;
		if (!(map_data[y1][x1] == 'a' || map_data[y1][x1] == 'b' || map_data[y1][x1] == 'c' || map_data[y1][x1] == 'g'))
			map_data[y1][x1] = 'c';
	}
}

void goal_flag() {
	int x1, y1;
		y1 = rand() % (MAP_SIZE - 2) + 1;
		x1 = rand() % (MAP_SIZE - 2) + 1;
		map_data[y1][x1] = 'g';
	}