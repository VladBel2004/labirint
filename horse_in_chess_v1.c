#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8

/*
 *   S
 * W   E
 *   N
 */
void start(int[][SIZE], int[]);
int can(int, int);
int try_do_this( const int[] );

int up_left   ( int[][SIZE], int[] );
int up_right  ( int[][SIZE], int[] );
int left_up   ( int[][SIZE], int[] );
int left_down ( int[][SIZE], int[] );
int down_left ( int[][SIZE], int[] );
int down_right( int[][SIZE], int[] );
int right_up  ( int[][SIZE], int[] );
int right_down( int[][SIZE], int[] );

void print_array( int field[][SIZE], int request[][SIZE] );
void copy_array( int *, int *, int );
int get_count_of_steps( int[][SIZE] );


int main( void )
{
        int pos[ 2 ] = { 0, 0 };
        int posc[ 2 ] = { 0 };

        while( 1 )
        {
                if( try_do_this( pos ) )
                {
                        break;
                }

                if( pos[ 0 ] == 7 && pos[ 1 ] == 7 )
                {
                        printf( "End!\n" );
                        break;
                }
                else if( pos[ 1 ] == 7 )
                {
                        pos[ 1 ] = 0;
                        ++pos[ 0 ];
                }
                else
                {
                        ++pos[ 1 ];
                }
        }
        return 0;
}

int try_do_this( const int pos[] )
{       
        int fied[SIZE][SIZE] = { 0 };
        int request[SIZE][SIZE] = { 0 };
        int posc[ 2 ] = { pos[ 0 ], pos[ 1 ] };
        int gy = pos[0], gx = pos[1];

        printf( "\n\tX: %d; Y: %d;\n", gx, gy );

        for( int y = 0; y < SIZE; y++ )
        {
                for( int x = 0; x < SIZE; x++ )
                {
                        if( down_left( fied, posc ) )
                        {
                                request[y][x] = 1;
                        }
                        else if( down_right( fied, posc ) )
                        {
                                request[y][x] = 2;
                        }
                        else if( left_down( fied, posc ) )
                        {
                                request[y][x] = 3;
                        }
                        else if( left_up( fied, posc ) )
                        {
                                request[y][x] = 4;
                        }
                        else if( right_down( fied, posc ) )
                        {
                                request[y][x] = 5;
                        }
                        else if( right_up( fied, posc ) )
                        {
                                request[y][x] = 6;
                        }
                        else if( up_left( fied, posc ) )
                        {
                                request[y][x] = 7;
                        }
                        else if( up_right( fied, posc ) )
                        {
                                request[y][x] = 8;
                        }
                        else
                        {
                                printf( "Count of steps: %d.\n", get_count_of_steps( fied ) );
                                printf( "\tNO NO NO NO!\n----------------------------------------------------------------\n");
                                return 0;
                        }
                }
        }
        printf( "Count of steps: %d.\n", get_count_of_steps( fied ) );
        print_array( fied, request );
        return 1;

}

void print_array( int field[][SIZE], int request[][SIZE] )
{
        for( int y = 0; y < SIZE; y++ )
        {
                for( int x = 0; x < SIZE; x++ )
                {
                        if( request[y][x] == 1 )
                        {
                                printf( "down_left.\n" );
                        }
                        else if( request[y][x] == 2 )
                        {
                                printf( "down_right.\n" );
                        }
                        else if( request[y][x] == 3 )
                        {
                                printf( "left_down.\n" );
                        }
                        else if( request[y][x] == 4 )
                        {
                                printf( "left_up.\n" );
                        }
                        else if( request[y][x] == 5 )
                        {
                                printf( "right_down.\n" );
                        }
                        else if( request[y][x] == 6 )
                        {
                                printf( "right_up.\n" );
                        }
                        else if( request[y][x] == 7 )
                        {
                                printf( "up_left.\n" );
                        }
                        else if( request[y][x] == 8 )
                        {
                                printf( "up_right.\n" );
                        }
                }
        }

        printf( "----------------------------------------------------------------\n" );

        for( int c = 0; c < SIZE * 2; c++ )
        {
                if( c == 0 )
                {
                        printf( "\n  %d ", c );
                }
                else if( c < SIZE )
                {
                        printf( "%d ", c );
                }
                else if( c == SIZE )
                {
                        printf( "\n  __" );
                }
                else
                {
                        printf( "__" );
                }
        }

        for( int y = 0; y < SIZE; y++ )
        {
                printf( "\n%d|", y );
                for( int x = 0; x < SIZE; x++ )
                {
                        printf( "%d ", field[y][x] );
                }
        }
        printf( "\n----------------------------------------------------------------\n\tCool!\n" );
}

void start(int array[][SIZE], int pos[])
{
	int x = pos[0], y = pos[1];
	array[y][x] = 1;
}

int up_left(int array[][SIZE], int pos[])
{
	int x = pos[0] - 1, y = pos[1] + 2;
	
	if(can(x, y) && array[y][x] == 0)
	{
		pos[0] -= 1;
		pos[1] += 2;
		++array[y][x];
		return 1;
	}
	else
	{
		return 0;
	}
}

int up_right(int array[][SIZE], int pos[])
{
	int x = pos[0] + 1, y = pos[1] + 2;

	if(can(x, y) && array[y][x] == 0)
	{
		pos[0] += 1;
		pos[1] += 2;
		++array[y][x];
		return 1;
	}
	else
	{
		return 0;
	}
}

int left_up(int array[][SIZE], int pos[])
{
	int x = pos[0] - 2, y = pos[y] + 1;

	if(can(x, y) && array[y][x] == 0)
	{
		pos[0] -= 2;
		pos[1] += 1;
		++array[y][x];
		return 1;
	}
	else
	{
		return 0;
	}
}

int left_down(int array[][SIZE], int pos[])
{
	int x = pos[0] - 2, y = pos[1] - 1;

	if(can(x, y) && array[y][x] == 0)
	{
		pos[0] -= 2;
		pos[1] -= 1;
		++array[y][x];
		return 1;
	}
	else
	{
		return 0;
	}
}

int down_left(int array[][SIZE], int pos[])
{
	int x = pos[0] - 1, y = pos[1] - 2;

	if(can(x, y) && array[y][x] == 0)
	{
		pos[0] -= 1;
		pos[1] -= 2;
		++array[y][x];
		return 1;
	}
	else
	{
		return 0;
	}
}

int down_right(int array[][SIZE], int pos[])
{
	int x = pos[0] + 1, y = pos[1] - 2;

	if(can(x, y) && array[y][x] == 0)
	{
		pos[0] += 1;
		pos[1] -= 2;
		++array[y][x];
		return 1;
	}
	else
	{
		return 0;
	}
}

int right_up(int array[][SIZE], int pos[])
{
	int x = pos[0] + 2, y = pos[1] + 1;

	if(can(x, y) && array[y][x] == 0)
	{
		pos[0] += 2;
		pos[1] += 1;
		++array[y][x];
		return 1;
	}
	else
	{
		return 0;
	}
}

int right_down(int array[][SIZE], int pos[])
{
	int x = pos[0] + 2, y = pos[1] - 1;

	if(can(x, y) && array[y][x] == 0)
	{
		pos[0] += 2;
		pos[1] -= 1;
		++array[y][x];
		return 1;
	}
	else
	{
		return 0;
	}
}

int can(int x, int y)
{
	if(x < SIZE && x >= 0 && y < SIZE && y >= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void copy_array( int *fromArr, int *toArr, int len )
{
        for( int i = 0; i < len; i++ )
        {
                toArr[ i ] = fromArr[ i ];
        }
}

int get_count_of_steps( int field[][SIZE] )
{
        int count = 0;
        for( int y = 0; y < SIZE; y++ )
        {
                for( int x = 0; x < SIZE; x++ )
                {
                        if( field[y][x] != 0 )
                        {
                                count++;
                        }
                }
        }
        return count;
}
