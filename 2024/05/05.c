#include <stdio.h>

#define LNSZ 512
#define RULES 1176
#define PAGES 64

struct rule
{
	int a, b;
};

int main(void)
{
	struct rule rules[RULES];
	int pages[PAGES];
	char line[LNSZ];

	int r = 0;

	int sum = 0;

	while (fgets(line, LNSZ, stdin) != NULL)
	{
		int p = 0;

		if (line[0] == '\0')
			continue;	

		if (line[2] == '|')
		{
			rules[r++] = (struct rule){
				.a = (line[0] - '0') * 10 + (line[1] - '0'),
				.b = (line[3] - '0') * 10 + (line[4] - '0')
			};
		}
		else
		{
			// preprocess
			int i = 0;
			do {
				pages[p++] = (line[i] - '0') * 10 + (line[i + 1] - '0');
				i += 2;
			} while (line[i++] == ',');

			// process
			int correct = 1;

			for (int pi = 0; pi < p; pi++)
			{
				for (int ri = 0; ri < r; ri++)
				{
					if (rules[ri].a == pages[pi])
					{
						for (int pj = 0; pj < pi; pj++)
						{
							if (pages[pj] == rules[ri].b)
								correct = 0;
						}
					}
				}
			}
			
			if (correct)
			{
				int middle = p / 2;
				sum += pages[middle];
			}
		}
	}

	printf("sum: %i\n", sum);

	return 0;
}

