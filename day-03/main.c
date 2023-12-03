#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ISDIGIT(c)\
	((c) >= '0' && (c) <= '9')

#define ISSPACE(c)\
	((c) <= ' ')

#define ISSYMBOL(c)\
	(!ISDIGIT(c) && !ISSPACE(c) && (c) != '.')

char **engine;
int w, h;

void load_engine(void)
{
	fseek(stdin, 0, SEEK_END);
	int size = ftell(stdin);
	fseek(stdin, 0, SEEK_SET);

	char line[512];
	fgets(line, 512, stdin);

	w = strlen(line) - 1;
	h = size / w;
	w++; h++;

	engine = malloc(h * sizeof(char*));
	for (int i = 0; i < h; i++)
		engine[i] = malloc(w);
	strlcpy(engine[0], line, w);

	int i = 1;
	while (fgets(line, 512, stdin) != NULL) {
		strlcpy(engine[i++], line, w);
	}
}

void free_engine(void)
{
	for (int i = 0; i < h; i++)
		free(engine[i]);
	free(engine);
}

int main(void)
{
	load_engine();

	int part = 0;
	int num = 0;
	int sum = 0;
	for (int i = 0; i < w * h; i++) {
		int x = i % w;
		int y = i / w;

		if (ISDIGIT(engine[y][x])) {
			num = num * 10 + (engine[y][x] - '0');

			int adjacent[8][2] = {
				{x - 1, y - 1},
				{x    , y - 1},
				{x + 1, y - 1},
				{x - 1, y    },
				{x + 1, y    },
				{x - 1, y + 1},
				{x    , y + 1},
				{x + 1, y + 1}
			};

			for (int j = 0; j < 8; j++) {
				int _x = adjacent[j][0];
				int _y = adjacent[j][1];
				if (_x < 0 || _x >= w || _y < 0 || _y >= h)
					continue;

				if (ISSYMBOL(engine[_y][_x])) {
					part = 1;
				}
			}
		} else {
			if (part) {
				sum += num;
			}

			part = num = 0;
		}

		printf("\e[%im%c\e[m", part ? 32 : 40, engine[y][x]);
		if (x == w - 1) {
			putc('\n', stdout);
		}
	}

	printf("%i\n", sum);
	free_engine();
	return 0;
}

