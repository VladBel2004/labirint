#include <stdio.h>

int main()
{
   int a, b, c, d, i;
   int small, hight;
   printf("Enter 5 values: \n");
   printf("A: ");
   scanf("%d", &a);

   printf("B: ");
   scanf("%d", &b);

   printf("C: ");
   scanf("%d", &c);

   printf("D: ");
   scanf("%d", &d);

   printf("I: ");
   scanf("%d", &i);

   if(a < b && a < c && a < d && a < i){ small = a; }
   else if(b < a && b < c && b < d && b < i){ small = b; }
   else if(c < a && c < b && c < d && c < i){ small = c; }
   else if(d < a && d < b && d < c && d < i){ small = d; }
   else{ small = i; }
   
   if(a != small && a > b && a > c && a > d && a > i){ hight = a; }
   else if(b != small && b > a && b > c && b > d && b > i){ hight = b; }
   else if(c != small && c > a && c > b && c > d && c > i){ hight = c; }
   else if(d != small && d > a && d > b && d > c && d > i){ hight = d; }
   else { hight = i; }
   printf("The smallest value in this range is %d \n\tand hightest value is %d\n", small, hight);
   return 0;
}
