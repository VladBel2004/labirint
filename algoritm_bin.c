#include <stdio.h>

int main()
{
	int value, count, v, c = 0, co = 0, col = 0;
	printf("Enter binary value: ");
	scanf("%d", &value);
	v = value;
	while(1)
	{
		if(v > 1)
		{
			v /= 10;
			count++;
		}
		else
		{
			count++;
			break;
		}
	}

	printf("S 1\n");

	if(count % 8 == 0)
	{
		col = value;
		v = 1;

		while(c < count)
		{
			int power = 1, con = 0;
			co = col % 10;
			col /= 10;
			if(co == 1)
			{
				while(con < c){ con++; power *= 2; }
				v += power;
				c++;
				con = 0;
				power = 1;
			}
			else
				c++;

		}
		printf("%d\n", v - 1);

	}
	else
		printf("value is not byte.\n");
	return 0;
}
