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

int possible_game(char *line, int *id)
{
	if (!match(line, "Game ")) {
		return 0;
	}

	line += 5;
	*id = read_int(&line);
	line += 2;
	
	int rsum = 0;
	int gsum = 0;
	int bsum = 0;
	while (*line && *line != '\n') {
		if (*line == ' ' || *line == ',') {
			line++;
		}

		if (*line == ';') {
			if (rsum > HAS_RED || gsum > HAS_GREEN || bsum > HAS_BLUE) {
				return 0;
			}

			rsum = gsum = bsum = 0;
			line++;
		}

		int n = read_int(&line);
		line++;
		if (match(line, "red")) {
			rsum += n;
			line += 3;
		} else if (match(line, "green")) {
			gsum += n;
			line += 5;
		} else if (match(line, "blue")) {
			bsum += n;
			line += 4;
		}
	}

	return !(rsum > HAS_RED || gsum > HAS_GREEN || bsum > HAS_BLUE);
}

int main(void)
{
	char line[128];
	int sum = 0;
	int id;

	while (fgets(line, 128, stdin) != NULL) {
		if (possible_game(line, &id)) {
			sum += id;
		}
	}

	printf("%i\n", sum);

	return 0;
}

