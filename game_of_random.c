#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
	int snumber, current, pop, count = 0;
	char youwant;
	srand(time(NULL));
	snumber = 1 + (rand() % 1000);
	
	while(1)
	{
		count++;

		if(count <= 10)
		{
			printf("Att %d - Enter number: ", count);
			scanf("%d", &current);
			if(current == snumber)
			{
				printf("You win!!!\n\tCount of your att is %d.\n", count);
				break;
			}
			else if(current < snumber)
				printf("Your number < Value.\n");
			else if(current > snumber)
				printf("Your number > Value.\n");
			else
				printf("Imposible.\n");
		}
		else
		{
			printf("You are lose, try agen.\n\tNumber was %d.\n", snumber);
			break;
		}
	}

	/* printf("Count of your attemps is %d.\n", pop + 1); */
}


