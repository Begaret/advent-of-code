#include <stdio.h>

#define HAS_RED		12
#define HAS_GREEN	13
#define HAS_BLUE	14

#define ISDIGIT(c)\
	((c) >= '0' && (c) <= '9')

int match(char *s1, char *s2)
{
	while (*s1 && *s2) {
		if (*s1 != *s2) {
			return 0;
		}

		s1++;
		s2++;
	}

	return 1; 
}

int read_int(char **s)
{
	int num = 0;
	while (**s && ISDIGIT(**s)) {
		num = num * 10 + (**s - '0');
		(*s)++;
	}

	return num;
}

int possible_game(char *line, int *id, int *pow)
{
	if (!match(line, "Game ")) {
		return 0;
	}

	line += 5;
	*id = read_int(&line);
	line += 2;

	int npos = 0;
	int rsum = 0, rmax = -1;
	int gsum = 0, gmax = -1;
	int bsum = 0, bmax = -1;
	while (*line && *line != '\n') {
		if (*line == ' ' || *line == ',') {
			line++;
		}

		if (*line == ';') {
			if (rsum > HAS_RED || gsum > HAS_GREEN || bsum > HAS_BLUE) {
				npos = 1;
			}

			rsum = gsum = bsum = 0;
			line++;
		}

		int n = read_int(&line);
		line++;
		if (match(line, "red")) {
			rsum += n;
			line += 3;
			if (n > rmax)
				rmax = n;
		} else if (match(line, "green")) {
			gsum += n;
			line += 5;
			if (n > gmax)
				gmax = n;
		} else if (match(line, "blue")) {
			bsum += n;
			line += 4;
			if (n > bmax)
				bmax = n;
		}
	}

	*pow = rmax * gmax * bmax;

	return npos ? 0 : !(rsum > HAS_RED || gsum > HAS_GREEN || bsum > HAS_BLUE);
}

int main(void)
{
	char line[1024];
	int sum = 0;
	int psum = 0;
	int id, pow;

	while (fgets(line, 1024, stdin) != NULL) {
		if (possible_game(line, &id, &pow)) {
			sum += id;
		}
		
		psum += pow;
	}

	printf("%i\n", sum);
	printf("%i\n", psum);

	return 0;
}

