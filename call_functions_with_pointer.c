#include "stdio.h"

void function1( void );
void function2( void );
void function3( void );
int can( int *, int );

int main( void )
{
      void( *f[3] )() = { function1, function2, function3 };
      int was[3] = { 0 };
      int current;

      while( can(was, 3) )
      {
              printf("Enter index and call function: ");
              scanf("%d", &current);
              if( was[current] == 0 )
              {
                      was[current] = 1;
                      ( *f[current] )();
              }
              else
              {
                      printf("Value not valude.\n");
                      continue;
              }
      }
      printf("The end.\n");
      return 0;
}

void function1( void )
{
       printf("Hello from Function1.\n"); 
}

void function2( void )
{
       printf("Hello from Function2.\n"); 
}

void function3( void )
{
       printf("Hello from Function3.\n"); 
}

int can( int *array, int max )
{
        int count = 0;

        for( int i = 0; i < max; i++ )
        {
                if(*( array + i ) == 0)
                {
                        continue;
                }
                else
                {
                        count++;
                }
        }

        if( count == max )
        {
                return 0;
        }
        else
        {
                return 1;
        }
}
