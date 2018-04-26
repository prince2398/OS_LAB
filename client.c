#include <stdio.h>

int main(int argc, char const *argv[])
{
	int  n = atoi(argv[1]);

	for (int i = 0; i < n; ++i)
	{
		printf("%d\t", i+1);
	}
	printf("\n");
	return 0;
}