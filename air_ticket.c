#include <stdio.h>

#define SIZE 10

int main(void)
{
	int array[SIZE] = { 0 };
	int value, fc, sc;

	printf("\tYou must fill plane,\n\t\tto stop typing -1.\n");

	while(1)
	{
		int can = 0;

		for(int i = 0; i < SIZE; i++)
		{
			if(array[i] > 0)
			{
				++can;
			}
		}
		if(can >= 10)
		{
			printf("This plane owerflow\n");
			break;
		}

		printf("Enter the seaton the plane: ");
		scanf("%d", &value);

		if(value == -1)
		{
			break;
		}


		if(array[value] == 0)
		{
			++array[value];
		}
		else
		{
			printf("This seat taken.\n");
		}
		printf("\n");
	}

	for(int i = 0; i < SIZE; i++)
	{
		if(array[i] > 0)
		{
			if(i < 4)
			{
				fc++;
			}
			else
			{
				sc++;
			}
		}
	}
	
	printf("\n\n");
	printf("\tNumber of passagires in first class is %d.\n\tAnd number of passagers in second class is %d.\n", fc, sc);	
}
