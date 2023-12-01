#include <stdlib.h>
#include <stdio.h>

#define ISDIGIT(c)\
	((c) >= '0' && (c) <= '9')

char *digits[] = {
	"zero", "one", 
	"two", "three", 
	"four", "five",
	"six", "seven",
	"eight", "nine"
};

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

int digit_str(char *s)
{
	for (int d = 0; d < 10; d++) {
		if (match(s, digits[d])) {
			return d;
		}
	}

	return -1;
}

int main(void)
{
	FILE *fp = fopen("input.txt", "r");

	int sum = 0;

	char *line = NULL;
	size_t len = 0;
	ssize_t bytes = 0;
	while ((bytes = getline(&line, &len, fp)) != -1) {
		char d1, d2;

		for (int i = 0; i < bytes; i++) {
			if (ISDIGIT(line[i])) {
				d1 = line[i] - '0';
				break;
			}

			int d = digit_str(line + i);
			if (d != -1) {
				d1 = d;
				break;
			}
		}

		for (int i = bytes - 1; i >= 0; i--) {
			if (ISDIGIT(line[i])) {
				d2 = line[i] - '0';
				break;
			}

			int d = digit_str(line + i);
			if (d != -1) {
				d2 = d;
				break;
			}
		}

		char num = d1 * 10 + d2;
		sum += num;
	}

	printf("sum: %i\n", sum);

	free(line);
	fclose(fp);
	return 0;
}

