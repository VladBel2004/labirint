#include "stdio.h"

#define SIZE 60
#define UP 1
#define Down 3
#define Left 2
#define Right 4

   /*2*/
 /*1   3*/
   /*4*/

int go( char map[][SIZE], int ratPos[], int direction, int *vector );
int canMove( const char map[][SIZE], int ratPos[], int *vector, int direction );
int isEnd( const char map[][SIZE], int ratPos[], int *vector );
int isDeadEnd( const char map[][SIZE], int ratPos[], int *vector, int *canLock );
int isInrersection( const char map[][SIZE], int ratPos[], int *vector );
void vectorInverse( int *vector );
void lock( char map[][SIZE], int *canLock, int ratPos[], int *vector );

int getPosOfChar( char symb, int pos[], char map[][SIZE] );
int canMoveHelp( char c );
void getStartPos( char map[][SIZE], int ratPos[], int *vector );
void printMap( const char map[][SIZE] );
void printRat( char map[][SIZE], int ratPos[] );

int main( void )
{
        char map[][SIZE] = {
                 "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
                 "#                                                         #",
                 "#                                                         #",
                 "#                 # # #                       # # #       #",
                 "#                 #   #                       #   #       #",
                 "#                 #   #                       #   #       #",
                 "#   # # # # # # # #   #                       #   #       #",
                 "#   #                 #                   # # #   # # # # #",
                 "#   # # # #   # # # # #                   #               E",
                 "#         #   #                           #   # # # # # # #",
                 "#         #   #           # # # # # # # # #   #           #",
                 "#         #   #           #                   #           #",
                 "#         #   #           #   # # # # # # #   #           #",
                 "# # # # # #   # # # # # # #   #           #   #           #",
                 "S                             #           #   #           #",
                 "# # # # # #   # # # # # # #   # # # # #   #   # # # #     #",
                 "#         #   #           #           #   #         #     #",
                 "#         #   #           # # # # # # #   #   # # # #     #",
                 "#         #   #                           #   #           #",
                 "#         #   #                           #   #           #",
                 "#   # # # #   # # # # # # #               #   #           #",
                 "#   #                     #     # # # # # #   # # # # #   #",
                 "#   # # # # # # # # # #   #     #                     #   #",
                 "#                     #   #     #   # # # # # # # #   #   #",
                 "#                     #   #     #   #             #   #   #",
                 "#                     #   #     #   #             #   #   #",
                 "#                     # # #     # # #             # # #   #",
                 "#                                                         #",
                 "#                                                         #",
                 "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # #"
        };
        int ratPos[2] = { 0 };
        int vector = 0, canLock = 0;

        getStartPos( map, ratPos, &vector );
        printf( "x: %d, y: %d;\n", ratPos[1], ratPos[0] );
        printRat( map, ratPos );
        printMap( map );
        printf( "Vector value: %d ( 1 - UP, 2 - Left, 3 - Down, 4 - Right ).\n", vector );
        printf( "Rat start move in the Labirint.\n" );

        while( 1 )
        {
                if( isEnd( map, ratPos, &vector ) )
                {
                        printMap( map );

                        printf( "Rat Find End of this Labirint.\n" );
                        break;
                }
                else if( isDeadEnd( map, ratPos, &vector, &canLock ) )
                {
                        printf( "\n" );
                        printRat( map, ratPos );
                        printMap( map );
                        printf( "%d.\n", canLock );
                        printf( "Vector value: %d ( 1 - UP, 2 - Left, 3 - Down, 4 - Right ).\n", vector );

                        vectorInverse( &vector );
                        canLock = 1;
                        printf( "Is Dead End.\n" );
                }
                else if( canLock && isInrersection( map, ratPos, &vector ) )
                {
                        printf( "\n" );
                        printRat( map, ratPos );
                        printMap( map );
                        printf( "Vector value: %d ( 1 - UP, 2 - Left, 3 - Down, 4 - Right ).\n", vector );

                        lock( map, &canLock, ratPos, &vector );
                        printf( "Rat Lock.\n" );
                }

                if( canMove( map, ratPos, &vector, Left ) )
                {
                        printf( "\n" );
                        printRat( map, ratPos );
                        printMap( map );
                        printf( "Vector value: %d ( 1 - UP, 2 - Left, 3 - Down, 4 - Right ).\n", vector );

                        
                        go( map, ratPos, UP, &vector );
                        printf( "Rat go Up.\n" );
                }
                else if( canMove( map, ratPos, &vector, UP ) )
                {       
                        printf( "\n" );
                        printRat( map, ratPos );
                        printMap( map );
                        printf( "Vector value: %d ( 1 - UP, 2 - Left, 3 - Down, 4 - Right ).\n", vector );

                        go( map, ratPos, Left, &vector );
                        printf( "Rat go Left.\n" );
                }
                else if( canMove( map, ratPos, &vector, Down ) )
                {       
                        printf( "\n" );
                        printRat( map, ratPos );
                        printMap( map );
                        printf( "Vector value: %d ( 1 - UP, 2 - Left, 3 - Down, 4 - Right ).\n", vector );

                        go( map, ratPos, Down, &vector );
                        printf( "Rat go Down.\n" );
                }
                else if( canMove( map, ratPos, &vector, Right ) )
                {
                        printf( "\n" );
                        printRat( map, ratPos );
                        printMap( map );
                        printf( "Vector value: %d ( 1 - UP, 2 - Left, 3 - Down, 4 - Right ).\n", vector );

                        go( map, ratPos, Right, &vector );
                        printf( "Rat go Right.\n" );
                }
                else
                {
                        printf( "Unknown error ( from main ).\n" );
                        return 0;
                }
        }

        return 0;
}

int go( char map[][SIZE], int ratPos[], int direction, int *vector )
{
        int *x = &ratPos[1], *y = &ratPos[0];
        if( direction == UP )
        {
                *vector = UP;
                *y -= 1;
                return 1;
        }
        else if( direction == Down )
        {
                *vector = Down;
                *y += 1;
                return 1;
        }
        else if( direction == Right )
        {
                *vector = Right;
                *x -= 2;
                return 1;
        }
        else if( direction == Left )
        {
                *vector = Left;
                *x += 2;
                return 1;
        }
        printf( "Directino value in go not currect.\n" );
        return 0;
}

void lock( char map[][SIZE], int *canLock, int ratPos[], int *vector )
{
        int cVector = *vector;
        int x = ratPos[1], y = ratPos[0];
        *canLock = 0;
        vectorInverse( &cVector );

        if( cVector == UP )
        {
                map[y - 1][x] = 'L';
        }
        else if( cVector == Down )
        {
                map[y + 1][x] = 'L';
        }
        else if( cVector == Left )
        {
                map[y][x + 2] = 'L';
        }
        else if( cVector == Right )
        {
                map[y][x - 2] = 'L';
        }
        else
        {
                printf( "Error in cVector value ( from lock ).\n" );
        }

}

int canMove( const char map[][SIZE], int *vector, int ratPos[], int direction )
{
        int x = ratPos[1], y = ratPos[0];

        if( direction != *vector )
        {
                if( direction == UP )
                {
                        if( canMoveHelp( map[ y - 1 ][ x ] ) )
                        {
                                return 1;
                        }
                }
                else if( direction == Down )
                {
                        if( canMoveHelp( map[ y + 1 ][ x ] ) )
                        {
                                return 1;
                        }
                }
                else if( direction == Right )
                {
                        if( canMoveHelp( map[ y ][ x - 2 ] ) )
                        {
                                return 1;
                        }
                }
                else if( direction == Left )
                {
                        if( canMoveHelp( map[ y ][ x + 2 ] ) )
                        {
                                return 1;
                        }
                }
                else
                {
                        return 0;
                }
        }
        else
        {
                return 0;
        }
}

int isEnd( const char map[][SIZE], int ratPos[], int *vector )
{
        int x = ratPos[1], y = ratPos[0];

        switch( *vector )
        {
                case UP:
                        if( map[ y + 1 ][ x ] == 'E' )
                        {
                                return 1;
                        }
                        break;

                case Down:
                        if( map[ y - 1 ][ x ] == 'E' )
                        {
                                return 1;
                        }
                        break;

                case Left:
                        if( map[ y ][ x - 2 ] == 'E' )
                        {
                                return 1;
                        }
                        break;

                case Right:
                        if( map[ y ][ x + 2 ] == 'E' )
                        {
                                return 1;
                        }
                        break;

                default:
                        printf( "Invalid value is *vector ( from isEnd ).\n" );
                        break;
        }
        return 0;
}

int isInrersection( const char map[][SIZE], int ratPos[], int *vector )
{
        int variants = 0;
        int x = ratPos[1], y = ratPos[0];

        switch( *vector )
        {
                case UP:
                        if( canMoveHelp( map[ y + 1 ][ x ] ) )
                        {
                                variants++;
                        }
                        if( canMoveHelp( map[ y ][ x + 2 ] ) )
                        {
                                variants++;
                        }
                        if( canMoveHelp( map[ y ][ x - 2 ] ) )
                        {
                                variants++;
                        }
                        break;

                case Down:
                        if( canMoveHelp( map[ y - 1 ][ x ] ) )
                        {
                                variants++;
                        }
                        if( canMoveHelp( map[ y ][ x + 2 ] ) )
                        {
                                variants++;
                        }
                        if( canMoveHelp( map[ y ][ x - 2 ] ) )
                        {
                                variants++;
                        }
                        break;

                case Left:
                        if( canMoveHelp( map[ y - 1 ][ x ] ) )
                        {
                                variants++;
                        }
                        if( canMoveHelp( map[ y + 1 ][ x ] ) )
                        {
                                variants++;
                        }
                        if( canMoveHelp( map[ y ][ x - 2 ] ) )
                        {
                                variants++;
                        }
                        break;

                case Right:
                        if( canMoveHelp( map[ y - 1 ][ x ] ) )
                        {
                                variants++;
                        }
                        if( canMoveHelp( map[ y + 1 ][ x ] ) )
                        {
                                variants++;
                        }
                        if( canMoveHelp( map[ y ][ x + 2 ] ) )
                        {
                                variants++;
                        }
                        break;

                default:
                        printf( "Invalid value in *vector ( from isInrersection ).\n" );
                        break;
        }
        if( variants > 1 )
        {
                return 1;
        }
        else if( variants <= 1 ) 
        {
                return 0;
        }
        else
        {
                return 0;
        }
}

int isDeadEnd( const char map[][SIZE], int ratPos[], int *vector, int *canLock )
{
        int variants = 3;
        int x = ratPos[1], y = ratPos[0];

        if( *vector == UP )
        {
                if( !canMoveHelp( map[ y + 1 ][ x ] ) )
                {
                        variants -= 1;
                }
                if( !canMoveHelp( map[ y ][ x + 2 ] ) )
                {
                        variants -= 1;
                }
                if( !canMoveHelp( map[ y ][ x - 2 ] ) )
                {
                        variants -= 1;
                }
        }
        else if( *vector == Down )
        {
                if( !canMoveHelp( map[ y - 1 ][ x ] ) )
                {
                        variants -= 1;
                }
                if( !canMoveHelp( map[ y ][ x + 2 ] ) )
                {
                        variants -= 1;
                }
                if( !canMoveHelp( map[ y ][ x - 2 ] ) )
                {
                        variants -= 1;
                }
        }
        else if( *vector == Left )
        {
                if( !canMoveHelp( map[ y + 1 ][ x ] ) )
                {
                        variants -= 1;
                }
                if( !canMoveHelp( map[ y - 1 ][ x ] ) )
                {
                        variants -= 1;
                }
                if( !canMoveHelp( map[ y ][ x - 2 ] ) )
                {
                        variants -= 1;
                }
        }
        else if( *vector == Right )
        {
                if( !canMoveHelp( map[ y + 1 ][ x ] ) )
                {
                        variants -= 1;
                }
                if( !canMoveHelp( map[ y - 1 ][ x ] ) )
                {
                        variants -= 1;
                }
                if( !canMoveHelp( map[ y ][ x + 2 ] ) )
                {
                        variants -= 1;
                }
        }
        else
        {
                printf( "Uncurrect value in vector ( this error from \'isDeadEnd\' ).\n" );
        }
        return variants;
}

void vectorInverse( int *vector )
{
        switch( *vector )
        {
                case UP:
                        *vector = Down;
                        break;

                case Down:
                        *vector = UP;
                        break;

                case Left:
                        *vector = Right;
                        break;

                case Right:
                        *vector = Left;
                        break;

                default:
                        printf( "Invalid value of *vector ( from vectorInverse ).\n" );
                        break;
        }
}

int getPosOfChar( char symb, int pos[], char map[][SIZE] )
{
        for( int y = 0; y < SIZE / 2; y++ )
        {
                for( int x = 0; x < SIZE; x++ )
                {
                        if( map[y][x] == symb )
                        {
                                pos[0] = y;
                                pos[1] = x;
                                return 1;
                        }
                }
        }
        return 0;
}

int canMoveHelp( char c )
{
        char errChars[] = { '#', 'S', 'E', 'L' };
        for( int i = 0; i < ( sizeof( errChars ) / sizeof( errChars[0] ) ); i++ )
        {
                if( c == errChars[i] )
                {
                        return 0;
                }
        }
        return 1;
}

void getStartPos( char map[][SIZE], int ratPos[], int *vector )
{
        int posOfStart[2] = { 0 };
        if( getPosOfChar( 'S', posOfStart, map ) )
        {
                if( posOfStart[ 0 ] == 0 && posOfStart[ 1 ] != 0 && posOfStart[ 1 ] != SIZE )
                {
                        *vector = Down;
                        posOfStart[ 0 ]++;
                }
                else if( posOfStart[ 0 ] == SIZE / 2 && posOfStart[ 1 ] != 0 && posOfStart[ 1 ] != SIZE )
                {
                        *vector = UP;
                        posOfStart[ 0 ]--;
                }
                else if( posOfStart[ 1 ] == 0 )
                {
                        *vector = Left;
                        posOfStart[ 1 ] += 2;
                }
                else if( posOfStart[ 1 ] == SIZE - 1 )
                {
                        *vector = Right;
                        posOfStart[ 1 ] -= 2;
                }

                ratPos[ 0 ] = posOfStart[ 0 ];
                ratPos[ 1 ] = posOfStart[ 1 ];
        }
        else 
        {
                printf( "Not found Start Position.\n" );
        }
}

void printMap( const char map[][SIZE] )
{
        for( int y = 0; y < SIZE / 2; y++ )
        {
                for( int x = 0; x < SIZE; x++ )
                {
                        printf( "%c", map[y][x] );
                }
                printf( "\n" ); 
        }
}

void printRat( char map[][SIZE], int ratPos[] )
{
        int oldRatPos[2] = { 0 };
        getPosOfChar( 'R', oldRatPos, map );

        map[oldRatPos[0]][oldRatPos[1]] = ' ';
        map[ratPos[0]][ratPos[1]] = 'R';
}
