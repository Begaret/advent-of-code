#include <stdio.h>

#define ISDIGIT(c)\
	((c) >= '0' && (c) <= '9')

#define ISSPACE(c)\
	((c) == ' ' || (c) == '\n')

char *num(char *p, int *i)
{
	int num = 0;
	while (ISDIGIT(*p)) {
		num = num * 10 + (*p++ - '0');
	}

	if (i) {
		*i = num;
	}

	return p;
}

char *match(char *p, char *q)
{
	while (*p && *q) {
		if (*p++ != *q++)
			break;
	}

	return p;
}

char *skip(char *p, char *q)
{
	while (*p == *q) {
		p++;
	}

	return p--;
}

#define SZ 10

int card(char *p)
{
	p = match(p, "Card");
	p = skip(p, " ");
	p = num(p, NULL);
	p = match(p, ":");
	p = skip(p, " ");

	int win[SZ];
	int i = 0;
	while (*p != '|') {
		p = num(p, &win[i++]);
		while (ISSPACE(*p)) {
			p++;
		}
	}
	
	p = match(p, "|");

	int points = 0;
	int n = 0;
	while (*p) {
		while (ISSPACE(*p))
			p++;

		p = num(p, &n);
		for (int i = 0; i < SZ; i++) {
			if (win[i] == n) {
				points = points ? points * 2 : 1;
			}
		}
	}

	return points;
}

int main(void)
{
	int sum = 0;

	char line[256];
	while (fgets(line, 256, stdin) != NULL) {
		sum += card(line);
	}

	printf("%i\n", sum);

	return 0;
}

