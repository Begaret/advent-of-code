#include <string.h>
#include <stdio.h>

#define LNSZ	512
#define GRDSZ	LNSZ	

int main(void)
{
	char grid[GRDSZ][GRDSZ];
	int w = 0, h = 0;

	char xmas[4] = "XMAS";

	char line[LNSZ];
	while (fgets(line, LNSZ, stdin) != NULL)
	{
		w = strlen(line);
		strlcpy(grid[h], line, LNSZ);
		h++;
	}

	int sum = 0;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (grid[y][x] == 'A')
			{
				if ((x - 1) >= 0 && (x + 1) < w
				 && (y - 1) >= 0 && (y + 1) < h
				 && ((grid[y - 1][x - 1] == 'M' && grid[y + 1][x + 1] == 'S')
				  || (grid[y - 1][x - 1] == 'S' && grid[y + 1][x + 1] == 'M'))
				 && ((grid[y - 1][x + 1] == 'M' && grid[y + 1][x - 1] == 'S')
				  || (grid[y - 1][x + 1] == 'S' && grid[y + 1][x - 1] == 'M')))
					sum++;
			}
		}
	}

	printf("%i\n", sum);

	return 0;
}

