#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 13

void print_header();
void in_array(int[], int);
void print_array(int[]);

int main(void)
{
	int array[SIZE] = { 0 };
	print_header();
	in_array(array, 30000);
	print_array(array);
}

void print_header()
{
	printf("\tNow you can see table of random:\n\n");
}

void in_array(int array[], int count)
{
	int first, second;

	srand(12);

	for(int i = 0; i < count; i++)
	{
		first  = 1 + rand() % 6;
		second = 1 + rand() % 6;
		++array[first + second];
	}
}

void print_array(int array[])
{
	int large = 0, middle;

	for(int i = 2; i < SIZE; i++)
	{
		if(array[i] > large)
		{
			large = array[i];
		}
	}

	middle = large / 20;

	for(int i = 2; i < SIZE; i++)
	{
		printf("\t\tNumber %2d - ", i);
		for(int b = 0; b < array[i] / middle; b++)
		{
			printf("*");
		}
		printf("\n");
	}
	printf("\n");
}
