#include <stdio.h>
#include <math.h>

long reverse(long);
int count(long);

int main(void)
{
	long value;
	printf("Enter value and reverse it: ");
	scanf("%ld", &value);
	printf("\nValue is: %16ld\n", reverse(value));
	return 0;
}  
long reverse(long arg)
{
	double val = 0.0, this;
	int cou = count(arg);
	
	for(int i = 0; i < cou; i++)
	{
		val += (arg % 10) / pow((double)10, (double)i + 1);
		/* printf("%10.12lf\n", val); */
		arg /= 10;
	}
	val = val * pow((double)10, (double)cou);
	return (long)val;
}

int count(long arg)
{
	int count = 0;
	while(1)
	{
		if(arg > 9)
		{
			count++;
			arg /= 10;
		}
		else
		{
			count++;
			break;
		}
	}
	return count;
}
