#include "stdio.h"

#define SIZE_MAP_Y 30
#define SIZE_MAP_X 62

// Enums
enum bool_e
{
        true,
        false,
};

enum vector_e
{
        null,
        up,
        down,
        left,
        right
};

enum req_e
{
        req_null,
        ok,
        err,
        dead_end,
        fork,
};

// Defs. of structs
struct movableDirections_t 
{
        enum bool_e m_up;
        enum bool_e m_down;
        enum bool_e m_left;
        enum bool_e m_right;
};

struct position_t
{
        int x;
        int y;
};

struct mouse_t
{
        struct position_t mouse_pos;
        enum vector_e lock_direction;
        enum bool_e dead_end;
        struct position_t forkable_position;
};

struct def 
{
        struct mouse_t mouse;
};

// Type def.
typedef enum req_e req_e;
typedef enum vector_e vector_e;
typedef enum bool_e bool_e;
typedef struct position_t position_t;
typedef struct mouse_t mouse_t;
typedef struct def def;
typedef struct movableDirections_t movableDirections_t;

// Defs. of Func. to Mouse
req_e mouseMove( def *, char map[SIZE_MAP_Y][SIZE_MAP_X] );
req_e printMap( def *, char map[SIZE_MAP_Y][SIZE_MAP_X] );
req_e checkEnd( def *, char map[SIZE_MAP_Y][SIZE_MAP_X] );
req_e checkPos( def *, char map[SIZE_MAP_Y][SIZE_MAP_X], movableDirections_t *md );
req_e initMouse( def *, char map[SIZE_MAP_Y][SIZE_MAP_X] );

int main( void )
{
        char map[SIZE_MAP_Y][SIZE_MAP_X] =
        {
                "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # ",
                "#                                                          #",
                "#                                                          #",
                "#                                                          #",
                "#                                                          #",
                "#                                                          #",
                "#       # # # # # # # # # # # # #                          #",
                "#       #                       #                          #",
                "#       # # # # # # #   # # # # #                          #",
                "#                   #   #                     # # # # # # # ",
                "#                   #   #                     #            E",
                "# # # # # # # # # # #   # # # # # # # # # # # #   # # # # # ",
                "S                                                 #        #",
                "# # # # # # # # # # # # #   # # # # # # # # # # # #        #",
                "#                       #   #                              #",
                "#                       #   #                              #",
                "#                       #   #   # # #                      #",
                "#                       #   #   #   #                      #",
                "#           # # # # # # #   # # #   #                      #",
                "#           #                       #                      #",
                "#           #   # # # # # # # # # # #                      #",
                "#           #   #                                          #",
                "#           # # #                                          #",
                "#                                                          #",
                "#                                                          #",
                "#                                                          #",
                "#                                                          #",
                "#                                                          #",
                "#                                                          #",
                "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # "
        };
        def mainDef = 
        {
                .mouse =
                {
                        .mouse_pos = 
                        {
                                .x = 0,
                                .y = 0,
                        },
                        .lock_direction = null,
                        .dead_end = true,
                        .forkable_position =
                        {
                                .x = 0,
                                .y = 0,
                        }
                },
        };

        initMouse( &mainDef, map );

        while( 1 )
        {
               mouseMove( &mainDef, map );
               printMap( &mainDef, map );
        }

        return 0;
}

req_e initMouse( def * defs, char map[][SIZE_MAP_X] )
{
        // ref of Mouse Pos
        int *x = &defs->mouse.mouse_pos.x;
        int *y = &defs->mouse.mouse_pos.y;

        // Mouse Lock Direction.
        vector_e *local_ldir = &defs->mouse.lock_direction;

        for( int ly = 0; ly < SIZE_MAP_Y; ly++ )
        {
                for( int lx = 0; lx < SIZE_MAP_X; lx++ )
                {
                        if( map[ly][lx] == 'S' )
                        {
                                if( lx == 0 )
                                {
                                        *local_ldir = left;

                                        *x = lx + 2;
                                        *y = ly;

                                }
                                else if( lx == SIZE_MAP_Y * 2 - 1 )
                                {
                                        *local_ldir = right;

                                        *x = lx - 2;
                                        *y = ly;
                                }
                                else if( ly == 0 )
                                {
                                        *local_ldir = up;

                                        *x = lx;
                                        *y = ly - 1;
                                }
                                else if( ly == SIZE_MAP_Y - 1 )
                                {
                                        *local_ldir = down;

                                        *x = lx;
                                        *y = ly + 1;
                                }
                        }
                }
        }

        return ok;
}

req_e mouseMove( def * defs, char map[SIZE_MAP_Y][SIZE_MAP_X] )
{
        // Def of Movable Directs.
        movableDirections_t local_md = 
        {
                .m_left = true,
                .m_right = true,
                .m_down = true,
                .m_up = true
        };
        
        // Mouse Lock Direction.
        vector_e *local_ldir = &defs->mouse.lock_direction;

        // Mouse positions.
        position_t *mouse_pos = &defs->mouse.mouse_pos;

        // Def request.
        req_e request = req_null;

        // Get options.
        request = checkPos( defs, map, &local_md );

        // Error Side of Map.
        int err_bit = 0;

        // If was returned forck.
        if( request == fork )
        {
                //  This Def is Define of Can Mouse in this Fork to put F Mark.
                int avaliabality_of_f_mark = 1;

                // Make the check easy.
                int m_x = mouse_pos->x;
                int m_y = mouse_pos->y;

                // Chack F Mark
                if( map[m_y - 1][m_x] == 'F' ||             // Check the Down Side.
                                map[m_y + 1][m_x] == 'F' || // Check the Up Side.
                                map[m_y][m_x + 2] == 'F' || // Chack the Right Side.
                                map[m_y][m_x - 2] == 'F' )  // Check the Left Side.
                {
                        avaliabality_of_f_mark = 0;
                }

                if( avaliabality_of_f_mark )
                {
                        // Set the F Mask to Up Side regerding Mouse Pos.
                        if( *local_ldir == up )
                        {
                                map[m_y + 1][m_x] = 'F';
                        }

                        // Set the F Mark to Down Side regerding Mouse Pos.
                        else if( *local_ldir == down )
                        {
                                map[m_y - 1][m_x] = 'F';
                        }

                        // Set the F Mask to Left Side regerding Mouse Pos.
                        else if( *local_ldir == left )
                        {
                                map[m_y][m_x - 2] = 'F';
                        }

                        // Set the F Mask to Right Side regerding Mouse Pos.
                        else if( *local_ldir == right )
                        {
                                map[m_y][m_x + 2] = 'F';
                        }

                        defs->mouse.forkable_position.x = m_x;
                        defs->mouse.forkable_position.y = m_y;
                }
        }

        // If req is dead_end.
        else if( request == dead_end )
        {
                puts( "The Dead_End Complete." );

                if( *local_ldir == up )
                {
                        *local_ldir = down;
                }
                else if( *local_ldir == down )
                {
                        *local_ldir = up;
                }
                else if( *local_ldir == left )
                {
                        *local_ldir = right;
                }
                else if( *local_ldir == right )
                {
                        *local_ldir = left;
                }

                // Return that this is dead_end.
                return dead_end;
        }

        // Select direction for Mouse.
        if( request == ok || request == fork )
        {
                // If ldir is Up.
                if( *local_ldir == up )
                {
                        // Check down.
                        if( local_md.m_down == true )
                        {
                                // Can Mouse go to down.
                                if( ( mouse_pos->y + 1 ) > ( SIZE_MAP_Y + 1 ) )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->y += 1;

                                // Set Lock Direction.
                                *local_ldir = down;
                        }

                        // Check right.
                        else if( local_md.m_right == true )
                        {
                                // Can Mouse go to right.
                                if( ( mouse_pos->x + 2 ) > ( SIZE_MAP_X - 1 ) )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->x += 2; 

                                // Set Lock Direction.
                                *local_ldir = up;
                        }

                        // Check left.
                        else if( local_md.m_left == true )
                        {
                                // Can Mouse go to left.
                                if( ( mouse_pos->x - 2 ) < 0 )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->x -= 2;

                                // Set Lock Direction.
                                *local_ldir = right;
                        }
                }

                // If ldir is Right.
                else if( *local_ldir == right )
                {
                        // Check up.
                        if( local_md.m_up == true )
                        {
                                // Can Mouse go to up.
                                if( ( mouse_pos->y - 1 ) < 0 )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->y -= 1;

                                // Set Lock Direction.
                                *local_ldir = left;
                        }

                        // Check down.
                        else if( local_md.m_down == true )
                        {
                                // Can Mouse go to down.
                                if( ( mouse_pos->y + 1 ) > ( SIZE_MAP_Y + 1 ) )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->y += 1;

                                // Set Lock Direction.
                                *local_ldir = up;
                        }

                        // Check left.
                        else if( local_md.m_left == true )
                        {
                                // Can Mouse go to left.
                                if( ( mouse_pos->x - 2 ) < 0 )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->x -= 2;

                                // Set Lock Direction.
                                *local_ldir = right;
                        }

                }

                // If ldir is Down.
                else if( *local_ldir == down )
                {
                        // Check up.
                        if( local_md.m_up == true )
                        {
                                // Can Mouse go to up.
                                if( ( mouse_pos->y - 1 ) < 0 )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->y -= 1;

                                // Set Lock Direction.
                                *local_ldir = down;
                        }

                        // Check right.
                        else if( local_md.m_right == true )
                        {
                                // Can Mouse go to right.
                                if( ( mouse_pos->x + 2 ) > ( SIZE_MAP_X - 1 ) )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->x += 2;

                                // Set Lock Direction.
                                *local_ldir = left;
                        }

                        // Check left.
                        else if( local_md.m_left == true )
                        {
                                // Can Mouse go to left.
                                if( ( mouse_pos->x - 2 ) < 0 )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->x -= 2;

                                // Set Lock Direction.
                                *local_ldir = right;
                        }


                }

                // If ldir is Left.
                else if( *local_ldir == left )
                {
                        // Check up.
                        if( local_md.m_up == true )
                        {
                                // Can Mouse go to up.
                                if( ( mouse_pos->y - 1 ) < 0 )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->y -= 1;

                                // Set Lock Direction.
                                *local_ldir = down;
                        }

                        // Check right.
                        else if( local_md.m_right == true )
                        {
                                // Can Mouse go to right.
                                if( ( mouse_pos->x + 2 ) > ( SIZE_MAP_X - 1 ) )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->x += 2;

                                // Set Lock Direction.
                                *local_ldir = left;
                        }

                        // Check down.
                        else if( local_md.m_down == true )
                        {
                                // Can Mouse go to down.
                                if( ( mouse_pos->y + 1 ) > ( SIZE_MAP_Y + 1 ) )
                                {
                                        // Set err side var.
                                        err_bit = 1;
                                }

                                // Set Mouse Pos.
                                mouse_pos->y += 1;

                                // Set Lock Direction.
                                *local_ldir = up;
                        }
                }

                // Print err on dysplay if err_bit not eq NULL.
                if( err_bit )
                {
                        printf( "The position of Mouse is over for map. \n" );
                        return err;
                }
        }

        return ok;
}

req_e checkPos( def * defs, char map[SIZE_MAP_Y][SIZE_MAP_X], movableDirections_t *md )
{
        // Def of check Helper.
        int checkHelper( char symbol );

        // Mouse vectors.
        vector_e *local_ldir = &defs->mouse.lock_direction;

        // Mouse position.
        position_t *mouse_pos = &defs->mouse.mouse_pos;

        // Direction on map.
        int x = 0;
        int y = 0;

        // Count of possible options.
        int count = 3;

        if( *local_ldir == up )
        {
                // Check down direct.
                if( checkHelper( map[mouse_pos->y + 1][mouse_pos->x] ) )
                {
                        md->m_down = false;
                        count--;
                }

                // Check right direct.
                if( checkHelper( map[mouse_pos->y][mouse_pos->x + 2] ) )
                {
                        md->m_right = false;
                        count--;
                }

                // Check left direct.
                if( checkHelper( map[mouse_pos->y][mouse_pos->x - 2] ) )
                {
                        md->m_left = false;
                        count--;
                }

                // Set ldir in md.
                md->m_up = false;
        }
        else if( *local_ldir == down )
        {
                // Check up direct.
                if( checkHelper( map[mouse_pos->y - 1][mouse_pos->x] ) )
                {
                        md->m_up = false;
                        count--;
                }

                // Check left dirct.
                if( checkHelper( map[mouse_pos->y][mouse_pos->x - 2] ) )
                {
                        md->m_left = false;
                        count--;
                }

                // Check right direct.
                if( checkHelper( map[mouse_pos->y][mouse_pos->x + 2] ) )
                {
                        md->m_right = false;
                        count--;
                }

                // Set ldir in md.
                md->m_down = false;
        }
        else if( *local_ldir == left )
        {
                // Check up direct.
                if( checkHelper( map[mouse_pos->y - 1][mouse_pos->x] ) )
                {
                        md->m_up = false;
                        count--;
                }

                // Check down direct.
                if( checkHelper( map[mouse_pos->y + 1][mouse_pos->x] ) )
                {
                        md->m_down = false;
                        count--;
                }

                // Check right direct.
                if( checkHelper( map[mouse_pos->y][mouse_pos->x + 2] ) )
                {
                        md->m_right = false;
                        count--;
                }

                // Set ldir in md.
                md->m_left = false;
        }
        else if( *local_ldir == right )
        {
                // Check up direct.
                if( checkHelper( map[mouse_pos->y - 1][mouse_pos->x] ) )
                {
                        md->m_up = false;
                        count--;
                }

                // Check down dirct.
                if( checkHelper( map[mouse_pos->y + 1][mouse_pos->x] ) )
                {
                        md->m_down = false;
                        count--;
                }

                // Check left.
                if( checkHelper( map[mouse_pos->y][mouse_pos->x - 2] ) )
                {
                        md->m_left = false;
                        count--;
                }

                // Set ldir in md.
                md->m_right = false;
        }

        if( count > 1 )
        {
                return fork;
        }
        else if( count == 1 )
        {
                return ok;
        }
        else if( count == 0 )
        {
                defs->mouse.dead_end = true;
                return dead_end;
        }
}

int checkHelper( char symbol ) 
{
        printf( "Hello from Check Helper. ( '%c' )\n", symbol );

        // Array of errors chars.
        char err_symb[] = { '#', 'E', 'S', 'L', 'F' };
        
        for( int i = 0; i < ( sizeof( err_symb ) / sizeof( char ) ); i++ )
        {
                if( symbol == err_symb[i] )
                {
                        // Return that this char is error.
                        return 1;
                }
        }

        // Return that this char is not erreor.
        return 0;
}

req_e printMap( def * defs, char map[SIZE_MAP_Y][SIZE_MAP_X] )
{
        // Mouse position.
        position_t *mouse_pos = &defs->mouse.mouse_pos;

        for( int y = 0; y < SIZE_MAP_Y; y++ )
        {
                for( int x = 0; x < SIZE_MAP_X; x++ )
                {
                        if( x == mouse_pos->x && y == mouse_pos->y )
                        {
                                printf( "%c", 'M' );
                                continue;
                        }

                        printf( "%c", map[y][x] );
                }
                printf( "\n" );
        }
}
