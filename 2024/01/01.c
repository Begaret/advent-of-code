#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define LIST_MAX	1024

#define PARSE_INT(n, p)				   \
	while ((*p == ' ') || (*p == '\n'))\
		p++;                           \
                                       \
	while ((*p >= '0') && (*p <= '9')) \
	{                                  \
		n = (n * 10) + (*p - '0');     \
		p++;                           \
	}

int compare(const void *a, const void *b)
{
	const int *ia = (const int*)a;
	const int *ib = (const int*)b;
	return *ia - *ib;
}

int count(const int *l, size_t i, int v)
{
	int n = 0;
	for (int j = 0; j < i; j++)
	{
		if (l[j] == v)
			n++;
	}

	return n;
}

int main(void)
{
	size_t sz = 128;
	char buf[sz];

	int *l1 = alloca(LIST_MAX * sizeof(*l1));
	int *l2 = alloca(LIST_MAX * sizeof(*l2));
	size_t i1 = 0, i2 = 0;

	// read lists
	while (fgets(buf, sz, stdin) != NULL)
	{
		int n = 0, m = 0;
		char *p = buf;

		PARSE_INT(n, p);
		PARSE_INT(m, p);

		l1[i1++] = n;
		l2[i2++] = m;
	}
	
	printf("i1 = %zu\n", i1);
	printf("i2 = %zu\n", i2);

	if (i1 != i2)
		return 1;

	// sort lists
	qsort(l1, i1, sizeof(*l1), compare);
	qsort(l2, i2, sizeof(*l2), compare);
	
	// calculate sum
	int sum = 0;

	for (int i = 0; i < i1; i++)
	{
		sum += l1[i] * count(l2, i2, l1[i]);
	}

	printf("sum: %i\n", sum);

	return 0;
}

