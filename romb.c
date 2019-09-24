#include <stdio.h>

int main()
{
	int a, b, c, d, count, height, wieght;
	printf("Enter height: ");
	scanf("%d", &height);
	printf("Enter wieght: ");
	scanf("%d", &wieght);

	if(height % 2 && wieght % 2){
		for(a = 0; a < 3; a++)
		{
			if(a == 0)
			{
				c = (wieght - 1) / 2;
				count = 1;
				for(b = 0; b < (wieght - 1) / 2; b++)
				{
					for(d = 0; d < c; d++)
						printf(" ");
					for(d = 0; d < count; d++)
						printf("*");
					c--;
					count += 2;
					printf("\n");
				}
			}
			else if(a == 1)
			{
				for(b = 0; b < wieght; b++)
					printf("*");
				printf("\n");
			}
			else
			{
				c = 1;
				count = 2 * ((wieght - 1) / 2);
				for(b = 0; b < (wieght - 1) / 2; b++)
				{
					for(d = 0; d < c; d++)
						printf(" ");
					for(d = 0; d < count - 1; d++)
						printf("*");
					c++;
					count -= 2;
					printf("\n");
				}
			}
		}
	}
}
