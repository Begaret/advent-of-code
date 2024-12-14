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
			if (grid[y][x] == 'X')
			{
				// XMAS
				if ((x + 3) < w
				 && grid[y    ][x + 1] == 'M'
				 && grid[y    ][x + 2] == 'A'
				 && grid[y    ][x + 3] == 'S')
					sum++;

				// SAMX
				if ((x - 3) >= 0
				 && grid[y    ][x - 1] == 'M'
				 && grid[y    ][x - 2] == 'A'
				 && grid[y    ][x - 3] == 'S')
					sum++;

				// X
				// M
				// A
				// S
				if ((y + 3) < h
				 && grid[y + 1][x    ] == 'M'
				 && grid[y + 2][x    ] == 'A'
				 && grid[y + 3][x    ] == 'S')
					sum++;

				// S
				// A
				// M
				// X
				if ((y - 3) >= 0
				 && grid[y - 1][x    ] == 'M'
				 && grid[y - 2][x    ] == 'A'
				 && grid[y - 3][x    ] == 'S')
					sum++;

				// X
				//  M
				//   A
				//    S
				if ((x + 3) < w && (y + 3) < h
				 && grid[y + 1][x + 1] == 'M'
				 && grid[y + 2][x + 2] == 'A'
				 && grid[y + 3][x + 3] == 'S')
					sum++;

				//    X
				//   M
				//  A
				// S
				if ((x - 3) >= 0 && (y + 3) < h
				 && grid[y + 1][x - 1] == 'M'
				 && grid[y + 2][x - 2] == 'A'
				 && grid[y + 3][x - 3] == 'S')
					sum++;

				// S
				//  A
				//   M
				//    X
				if ((x - 3) >= 0 && (y - 3) >= 0
				 && grid[y - 1][x - 1] == 'M'
				 && grid[y - 2][x - 2] == 'A'
				 && grid[y - 3][x - 3] == 'S')
					sum++;

				//    S
				//   A
				//  M
				// X
				if ((x + 3) < w && (y - 3) >= 0
				 && grid[y - 1][x + 1] == 'M'
				 && grid[y - 2][x + 2] == 'A'
				 && grid[y - 3][x + 3] == 'S')
					sum++;
			}
		}
	}

	printf("%i\n", sum);

	return 0;
}

