#include <stdio.h>

int perfect(int);

int main(void)
{
	for(int i = 0; i < 100000; i++)
	{
		if(perfect(i))
		{
			printf("Number: %7d perfect.\n", i);
		}
	}
}

int perfect(int arg)
{
	int count = 0;
	for(int i = 1; i < arg; i++)
	{
		if(!(arg % i))
		{
			count += i;
			if(count == arg)
				return 1;
		}
	}
	return 0;
}
