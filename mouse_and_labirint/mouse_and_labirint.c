#include <stdio.h>
#include <string.h>
#include "./header.h"

#define CORDS_X 39
#define CORDS_Y 20
#define ARRAY_SIZE 10

#define can_go check

struct position get_char_position( char c );
int init_mouse();
void print_labirint();
int mouse_movement( enum direction dir );
int check( enum direction dir );
enum mStatus check_mStatus();
enum direction neg_dir( enum direction dir );
int is_end();
int mouse_manager();

struct position pop( struct position array[], int size_array );
int push( struct position array[], struct position value, int size_array );
void array_init( struct position array[], int size_array );
struct position preview( struct position array[], int size_array );

void statusPrint( enum mStatus );
void mouse_clear();

char labirint[CORDS_Y][CORDS_X] = {
        "# # # # # # # # # # # # # # # # # # # #",
        "#                                     #",
        "#                                     #",
        "#                                     #",
        "#                                     #",
        "#                                     #",
        "#                                     #",
        "#                                     #",
        "#                                     #",
        "# # # # # # # # # # # #               #",
        "E                     #               #",
        "# # # # # # #   ###   #               #",
        "#           #   ###   #               #",
        "#           #   ###   #               #",
        "#           #         #               #",
        "#           # # # #   #               #",
        "#                 #   #               #",
        "#                 #   #               #",
        "#                 #   #               #",
        "# # # # # # # # # # S # # # # # # # # #"
};

enum direction last_dir;
struct position exits_form_forks[ARRAY_SIZE];
struct position forks[ARRAY_SIZE];

int main( void )
{
        array_init( exits_form_forks, ARRAY_SIZE );
        array_init( forks, ARRAY_SIZE );

        init_mouse();

        mouse_manager();

        return 0;
}

int mouse_manager()
{
        enum mStatus mStat;
        struct position pos;
        struct position prev;

        do
        {
                pos = get_char_position( 'M' );
                prev = preview( forks, ARRAY_SIZE );

                if( prev.x == pos.x && prev.y == pos.y )
                {
                        // Lock last Dirif( last_dir == up )
                        if( last_dir == up )
                                labirint[pos.y + 1][pos.x] = 'L'; 

                        else if( last_dir == right )
                                labirint[pos.y][pos.x - 2] = 'L'; 

                        else if( last_dir == down )
                                labirint[pos.y - 1][pos.x] = 'L'; 

                        else if( last_dir == left )
                                labirint[pos.y][pos.x + 2] = 'L';

                        // Cheese Direction
                        if( can_go( up ) )
                                mouse_movement( up );

                        else if( can_go( right ) )
                                mouse_movement( right );

                        else if( can_go( down ) )
                                mouse_movement( down );

                        else if( can_go( left ) )
                                mouse_movement( left );
                }


                mStat = check_mStatus();

                if( mStat == corridor )
                {
                        mouse_movement( last_dir );
                }

                else if( mStat == fork )
                {
                        // Lock back and PUSH Exit Form Fork
                        if( last_dir == up )
                        { 
                                labirint[pos.y + 1][pos.x] = 'L'; 
                                push( exits_form_forks, (struct position){ .x = pos.x, .y = pos.y + 1 }, ARRAY_SIZE );
                        }

                        else if( last_dir == right )
                        { 
                                labirint[pos.y][pos.x - 2] = 'L'; 
                                push( exits_form_forks, (struct position){ .x = pos.x - 2, .y = pos.y }, ARRAY_SIZE );
                        }

                        else if( last_dir == down )
                        { 
                                labirint[pos.y - 1][pos.x] = 'L'; 
                                push( exits_form_forks, (struct position){ .x = pos.x, .y = pos.y - 1 }, ARRAY_SIZE );
                        }

                        else if( last_dir == left )
                        {
                                labirint[pos.y][pos.x + 2] = 'L';
                                push( exits_form_forks, (struct position){ .x = pos.x + 2, .y = pos.y }, ARRAY_SIZE );
                        }

                        // Push Mouse Position
                        push( forks, pos, ARRAY_SIZE );

                        // Select Direction
                        if( can_go( up ) )
                                mouse_movement( up );

                        else if( can_go( right ) )
                                mouse_movement( right );

                        else if( can_go( down ) )
                                mouse_movement( down );

                        else if( can_go( left ) )
                                mouse_movement( left );
                }

                else if( mStat == dead_end )
                {
                        last_dir = neg_dir( last_dir );
                }

                else if( mStat == box )
                {
                        struct position lockPos = pop( exits_form_forks, ARRAY_SIZE );
                        
                        // REMOVE this Fork From Array
                        pop( forks, ARRAY_SIZE );

                        // OPEN Exit
                        labirint[lockPos.y][lockPos.x] = ' ';

                        // Change Mouse Direction
                        if( lockPos.x > pos.x )
                                mouse_movement( right );

                        else if( lockPos.x < pos.x )
                                mouse_movement( left );

                        else if( lockPos.y < pos.y )
                                mouse_movement( up );

                        else if( lockPos.y > pos.y )
                                mouse_movement( down );
                }

                else if( mStat == angle )
                {
                        if( last_dir == up )
                        {
                                if( can_go( up ) )
                                        mouse_movement( up );

                                else if( can_go( right ) )
                                        mouse_movement( right );

                                else if( can_go( left ) )
                                        mouse_movement( left );
                        }

                        else if( last_dir == right )
                        {
                                if( can_go( up ) )
                                        mouse_movement( up );

                                else if( can_go( right ) )
                                        mouse_movement( left );

                                else if( can_go( down ) )
                                        mouse_movement( down );
                        }

                        else if( last_dir == down )
                        {
                                if( can_go( right ) )
                                        mouse_movement( right );

                                else if( can_go( down ) )
                                        mouse_movement( down );

                                else if( can_go( left ) )
                                        mouse_movement( left );
                        }

                        else if( last_dir == left )
                        {
                                if( can_go( up ) )
                                        mouse_movement( up );

                                else if( can_go( down ) )
                                        mouse_movement( down );

                                else if( can_go( left ) )
                                        mouse_movement( left );
                        }
                }

                // PRINT Labirint
                print_labirint();
                printf( "\n" );
        }
        while( mStat != end );

        printf( "Mouse Come to End.\n" );

        return 1;
}

enum mStatus check_mStatus()
{
        struct position pos;
        enum mStatus mStat;

        pos = get_char_position( 'M' );

        int ways = 3;

        // PRINT Error
        if( pos.x == 99 && pos.y == 99 )
        {
                printf( "ERROR. (check_mStatus)\n" );
                return 0;
        }

        if( last_dir == up )
        {
                if( !can_go( up ) )
                        ways -= 1;
                if( !can_go( right ) )
                        ways -= 1;
                if( !can_go( left ) )
                        ways -= 1;
        }

        else if( last_dir == right )
        {
                if( !can_go( up ) )
                        ways -= 1;
                if( !can_go( right ) )
                        ways -= 1;
                if( !can_go( down ) )
                        ways -= 1;
        }

        else if( last_dir == down )
        {
                if( !can_go( right ) )
                        ways -= 1;
                if( !can_go( down ) )
                        ways -= 1;
                if( !can_go( left ) )
                        ways -= 1;
        }

        else if( last_dir == left )
        {
                if( !can_go( up ) )
                        ways -= 1;
                if( !can_go( down ) )
                        ways -= 1;
                if( !can_go( left ) )
                        ways -= 1;
        }

        if( ways == 0 && !can_go( neg_dir( last_dir ) ) )
        {
                return ( mStat = box );
        }

        else if( ways == 0 )
        {
                if( is_end() )
                {
                        return ( mStat = end );
                }

                return ( mStat = dead_end );
        }

        else if( ways == 1 )
        {
                if( !can_go( last_dir ) )
                {
                        return ( mStat = angle );
                }
                return ( mStat = corridor );
        }

        else if( ways >= 2 )
        {
                return ( mStat = fork );
        }
}

int mouse_movement( enum direction dir )
{
        struct position pos;

        pos = get_char_position( 'M' );

        // PRINT Error
        if( pos.x == 99 && pos.y == 99 )
        {
                printf( "ERROR. (mouse_movement)\n" );
                return 0;
        }

        // Clear MOUSE
        labirint[pos.y][pos.x] = ' ';

        // MOUSE Movement
        if( dir == up )
        {
                last_dir = up;

                labirint[pos.y - 1][pos.x] = 'M';
        }
        else if( dir == down )
        {
                last_dir = down;

                labirint[pos.y + 1][pos.x] = 'M';
        }
        else if( dir == right )
        {
                last_dir = right;

                labirint[pos.y][pos.x + 2] = 'M';
        }
        else if( dir == left )
        {
                last_dir = left;

                labirint[pos.y][pos.x - 2] = 'M';
        }

        return 1;
}

void print_labirint()
{
        for( int y = 0; y < CORDS_Y; y++ )
        {
                for( int x = 0; x < CORDS_X; x++ )
                {
                        printf( "%c", labirint[y][x] );
                }

                printf( "\n" );
        }
}

int init_mouse()
{
        struct position pos;

        pos = get_char_position( 'S' );

        // PRINT Error
        if( pos.y == 99 && pos.x == 99 )
        {
                printf( "ERROR. (init_mouse)\n" );
                return 0;
        }

        if( pos.x == 0 )
        {
                labirint[pos.y][pos.x + 2] = 'M';
                
                last_dir = right;
        }

        else if( pos.y == 0 )
        {
                labirint[pos.y + 1][pos.x] = 'M';

                last_dir = down;
        }

        else if( pos.x == CORDS_X - 1 )
        {
                labirint[pos.y][pos.x - 2] = 'M';

                last_dir = left;
        }

        else if( pos.y == CORDS_Y - 1 )
        {
                labirint[pos.y - 1][pos.x] = 'M';

                last_dir = up;
        }

        return 1;
}

struct position get_char_position( char c )
{
        struct position pos;

        for( int y = 0; y < CORDS_Y; y++ )
        {
                for( int x = 0; x < CORDS_X; x++ )
                {
                        if( c == labirint[y][x] )
                        {
                                pos.x = x;
                                pos.y = y;

                                return pos;
                        }
                }
        }

        // PRINT Error
        printf( "ERROR. (get_char_position)\n" );

        pos.x = 99;
        pos.y = 99;

        return pos;
}

int check( enum direction dir )
{
        struct position pos;
        char c;
        char block[] = { '#', 'L', 'S', 'E' };

        pos = get_char_position( 'M' );

        // PRINT Error
        if( pos.x == 99 && pos.y == 99 )
        {
                printf( "ERROR. (check)\n" );
                return 0;
        }

        if( dir == up )
                c = labirint[pos.y - 1][pos.x];
        else if( dir == right )
                c = labirint[pos.y][pos.x + 2];
        else if( dir == down )
                c = labirint[pos.y + 1][pos.x];
        else if( dir == left )
                c = labirint[pos.y][pos.x - 2];

        for( int i = 0; i < sizeof( block ) / sizeof( char ); i++ )
        {
                if( c == block[i] )
                {
                        return 0;
                }
        }

        return 1;
}

int is_end()
{
        struct position pos = get_char_position( 'M' );

        if( pos.x == 99 && pos.y == 99 )
        {
                printf( "ERROR. (is_end)\n" );
                return 0;
        }

        if( last_dir == up && labirint[pos.y - 1][pos.x] == 'E' )
                return 1;
        
        else if( last_dir == right && labirint[pos.y][pos.x + 2] == 'E' )
                return 1;
        
        else if( last_dir == down && labirint[pos.y + 1][pos.x] == 'E' )
                return 1;

        else if( last_dir == left && labirint[pos.y][pos.x - 2] == 'E' )
                return 1;

        else
                return 0;
}

enum direction neg_dir( enum direction dir )
{
        if( dir == up )
                return down;

        else if( dir == right )
                return left;

        else if( dir == down )
                return up;

        else if( dir == left )
                return right;
        
}

int push( struct position array[], struct position value, int size_array )
{
        int index;

        for( int i = 0; i < size_array; i++ )
        {
                if( array[i].x == 99 && array[i].y == 99 )
                {
                        index = i;
                        break;
                }
        }

        array[index] = value;
}

struct position pop( struct position array[], int size_array )
{
        int index = 99;
        struct position pos;

        for( int i = 0; i < size_array; i++ )
        {
                if( array[i].x != 99 && array[i].y != 99 )
                        index = i;
        }

        if( index == 99 )
        {
                printf( "this_array_is_empty.\n" );
                return (struct position){ .x = 99, .y = 99 };
        }

        pos = array[index];

        array[index] = (struct position){ .x = 99, .y = 99 };

        return pos;
}

void array_init( struct position array[], int size_array )
{
        for( int i = 0; i < size_array; i++ )
        {
                array[i] = (struct position){ .x = 99, .y = 99 };
        }
}

struct position preview( struct position array[], int size_array )
{
        for( int i = 0; i < ARRAY_SIZE; i++ )
        {
                if( array[i + 1].x == 99 && array[i + 1].y == 99 )
                {
                        return array[i];
                }
        }

        printf( "this_array_is_empty. (preview)\n" );

        return (struct position){ .x = 99, .y = 99 };
}

void statusPrint( enum mStatus stat )
{
        if( stat == end )
                printf( "END.\n" );

        else if( stat == dead_end )
                printf( "DEAD_END.\n" );

        else if( stat == corridor )
                printf( "CORRIDOR.\n" );

        else if( stat == fork )
                printf( "FORK.\n" );

        else if( stat == box )
                printf( "BOX.\n" );

        else if( stat == angle )
                printf( "ANGLE.\n" );
}

void mouse_clear()
{
        struct position pos;

        pos = get_char_position( 'M' );

        labirint[pos.y][pos.x] = ' ';
}
