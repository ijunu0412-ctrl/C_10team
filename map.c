#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void map();
int main()
{
	map();
	return 0;
}

void map()
{
	char map[20][20] = { 0 };
	char x1, y1;
	srand((unsigned)time);
	int i, j;
	for (i = 0;i < 20;i++)
	{
		for (j = 0;j < 20;j++)
			map[i][j] = ' ';
	}
	map[18][1] = 'b'; 
	for (i = 0;i < 20;i++)
	{
		map[0][i] = '#';
		map[i][0] = '#';
		map[19][i] = '#';
		map[i][19] = '#';
	}

	for (i = 0;i < 7;i++) {
		x1 = rand() % 18 + 1;
		y1 = rand() % 18 + 1;
		if (map[x1][y1] == 'a' || map[x1][y1] == 'b')
			i--;
		else
			map[x1][y1] = 'a';
	}

	for (i = 0;i < 20;i++) {
		for (j = 0;j < 20;j++) {
			if (map[i][j] == 'a')
				printf("¢º"); 
			else if (map[i][j] == 'b')
				printf("¡ß");
			else
				printf("%c", map[i][j]);
		}printf("\n");
	}

	return 0;
}