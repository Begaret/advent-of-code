#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define BUFSZ	17161	

int main(void)
{
	char buf[BUFSZ];
	int sz = fread(buf, 1, BUFSZ, stdin);
	int sum = 0;

	int do_mul = 1;

	for (int i = 0; i < sz; i++)
	{
		if (do_mul && memcmp(&buf[i], "mul(", 4) == 0)
		{
			i += 4;

			int n = 0;
			while (buf[i] >= '0' && buf[i] <= '9')
				n = (n * 10) + (buf[i++] - '0');

			if (buf[i++] != ',')
				continue;

			int m = 0;
			while (buf[i] >= '0' && buf[i] <= '9')
				m = (m * 10) + (buf[i++] - '0');
			
			if (buf[i] != ')')
				continue;

			sum += n * m;
		}
		else if (memcmp(&buf[i], "don't()", 7) == 0)
		{
			do_mul = 0;
		}
		else if (memcmp(&buf[i], "do()", 4) == 0)
		{
			do_mul = 1;
		}
	}

	printf("%i\n", sum);

	return 0;
}

