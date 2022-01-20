#include <stdio.h>

int func(int n)
{
	static int* ptr;

	return (n + 1);
}

int main(void)
{

	printf("%d", func(a));
	return 0;
}