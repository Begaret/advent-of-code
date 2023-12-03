#include <stdlib.h>
#include <stdio.h>

#define ISDIGIT(c)\
	((c) >= '0' && (c) <= '9')

char *read(int *w, int *h)
{
	fseek(stdin, 0, SEEK_END);
	int n = ftell(stdin);
	fseek(stdin, 0, SEEK_SET);

	char *p = malloc(n + 1);
	char *s = p;

	int l = 0;
	int c;
	while ((c = fgetc(stdin)) != EOF) {
		if (c == '\n') {
			l ?: (l = s - p);
		} else {
			*s++ = c;
		}
	}

	p[n] = '\0';

	*w = l;
	*h = (n - 1) / *w;

	return p;
}

char *num(char *p)
{
	while (ISDIGIT(*p)) {
		p--;
	}

	return ++p;
}

int main(void)
{
	int w, h;
	char *p = read(&w, &h);
	char *q = p;

	int sum = 0;
	while (*q) {
		if (*q == '*') {
			int d[] = {
				-(w + 1), -(w + 0), -(w - 1),
				-(1    ), -(0    ), -(-1   ),
				+(w - 1), +(w + 0), +(w + 1)
			};

			char *k = NULL;
			int n = 0;
			int g = 1;
			for (int i = 0; i < 9; i++) {
				if (q - p > 0 && q - p < (w * h - 1)) {
					char *s = q + d[i];
					if (ISDIGIT(*s)) {
						char *tmp = num(s);
						if (tmp != k) {
							n++;
							g *= atoi(tmp);
							k = tmp;
						}
					}
				}
			}

			if (n == 2) {
				sum += g;
			}
		}

		q++;
	}

	printf("%i\n", sum);
	free(p);

	return 0;
}

