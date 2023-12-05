#include <stdio.h>

#define WIN 10
#define NUM 25
#define CRD 209

int cards[CRD];

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

void card(char *p)
{
	int id = 0;

	p = match(p, "Card");
	p = skip(p, " ");
	p = num(p, &id);
	p = match(p, ":");
	p = skip(p, " ");

	cards[id - 1] = 0;

	int win[WIN];
	int w = 0;
	while (*p != '|') {
		p = num(p, &win[w++]);
		while (ISSPACE(*p)) {
			p++;
		}
	}
	
	p = match(p, "|");

	int n = 0;
	while (*p) {
		while (ISSPACE(*p))
			p++;

		p = num(p, &n);
		for (int i = 0; i < WIN; i++) {
			cards[id - 1] += (win[i] == n);
		}
	}
}

int calc_sum(int id)
{
	if (cards[id - 1] == 0) {
		return 1;
	}

	int sum = 1;
	for (int _id = id + 1; _id <= id + cards[id - 1]; _id++) {
		sum += calc_sum(_id);
	}

	return sum;
}

int main(void)
{
	char line[256];
	while (fgets(line, 256, stdin) != NULL) {
		card(line);
	}

	int sum = 0;
	for (int id = 1; id <= CRD; id++) {
		sum += calc_sum(id);
	}

	printf("%i\n", sum);
	return 0;
}

