#include <stdio.h>

long fib(unsigned int);

int main(void)
{
	unsigned int number;
	long result;
	printf("Enter number: ");
	scanf("%u", &number);

	for(unsigned int i = 0; i < number; i++)
	{
		printf("Number %3u = Fib %ld\n", i+1, fib(i+1));
	}
	return 0;
}

long fib(unsigned int num)
{
	if(num <= 0)
		return 0;
	else if(num < 3)
		return 1;
	else
	{
		long res, old = 1, cur = 1;

		for(int i = 2; i < num; i++)
		{
			res = old + cur;
			old = cur;
			cur = res;
		}
		return res;
	}
		/* return fib(res - 1) + fib(res - 2); */
}
