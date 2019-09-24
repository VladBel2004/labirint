#include <stdio.h>

int main()
{
	int count, t = 1;
	float x = 4.0;
	printf("Enter value: ");
	scanf("%d", &count);
	count += 3;

	for(int i = 3; i < count; i += 2)
	{
		if(t % 2)
		{
			x -= (float)4 / (float)i;
		}
		else
			x += (float)4 / (float)i;
		printf("Value is %12.12f.\n", x);
		t++;
	}
	t = 0;
	printf("The end.\n");
}
