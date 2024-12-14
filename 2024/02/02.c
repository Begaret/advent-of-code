#include <stdio.h>
#include <stdlib.h>

#define LNSZ	256	
#define SIGN(i)	( (i) < 0 ? -1 : 1 )

int report(char *line)
{
	int prev = 0;
	int dir = 0;
	int i = 0;

	while (i < LNSZ && line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			int n = 0;
			while (line[i] >= '0' && line[i] <= '9')
				n = (n * 10) + (line[i++] - '0');

			if (prev)
			{
				int d = n - prev;
				if (dir && (SIGN(d) != (SIGN(dir))))
					return 0;

				if (abs(d) < 1 || abs(d) > 3)
					return 0;

				dir = d;
			}

			prev = n;

			continue;
		}

		i++;
	}

	return 1;
}

int main(void)
{
	char line[LNSZ];
	int n = 0;

	while (fgets(line, LNSZ, stdin) != NULL)
	{
		n += report(line);
	}

	printf("%i\n", n);

	return 0;
}

