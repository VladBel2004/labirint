#include <stdio.h>

int main()
{
   	int size = 1, column = 0, indentation = 0;

	printf("Enter size of your sqare: ");
   	scanf("%d", &size);
	printf("Enter your indentation: ");
	scanf("%d", &indentation);

   	while(column < size)
   	{
		int row = 0;
		column++;
		while(row < size)
		{
			row++;

			if(column <= indentation || column >= size - indentation + 1)
				printf("* ");

			else if(row <= indentation)
				printf("* ");

			else if(row >= size - indentation + 1)
				printf("* ");

			else
				printf("  ");
		}
		printf("\n");
  	}
	return 0;
}
