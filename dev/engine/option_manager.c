#include "option_manager.h"
#include "enemy_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "gamer_manager.h"
#include "global_manager.h"
#include "locale_manager.h"
#include "score_manager.h"
#include "tile_manager.h"
#include "..\object\locale_object.h"

//#define OPTION_X		SCREEN_TILE_LEFT + 4
//#define OPTION_Y		TEXT1_Y + TEXT1_Y
#define SWAP_DELAY1		60
#define SWAP_DELAY2		3 * SWAP_DELAY1 / 2
#define SWAP_DELAY3		2 * SWAP_DELAY1

static unsigned char value_x[] = { OPTION_X + 0, OPTION_X + 5, OPTION_X + 12, OPTION_X + 17 };
static unsigned char value_y[] = { OPTION_Y + 0, OPTION_Y + 3, OPTION_Y + 6,  OPTION_Y + 10 };

static unsigned char delay_data1;
static unsigned char delay_data2;
static unsigned char delay_data3;
static unsigned char bonus_tile;
static unsigned char enemy_type;
static unsigned char location;
static unsigned char leftside;
static unsigned char distance;
//static unsigned char index;

void engine_option_manager_init( unsigned char sides )
{
	distance = sides;
	//index = sides;

	delay_data1 = 0;
	delay_data2 = 0;
	delay_data3 = 0;
	bonus_tile = tile_type_bonusA;
	enemy_type = actor_type_pro;
	location = 29;
	leftside = value_x[ 1 ];
}

void engine_option_manager_update( unsigned char screen )
{
	delay_data1++;
	delay_data2++;
	delay_data3++;
	if( delay_data1 >= SWAP_DELAY1 )
	{
		engine_enemy_manager_frame( enemy_type );
		delay_data1 = 0;

		enemy_type++;
		if( enemy_type >= MAX_ENEMIES )
		{
			enemy_type = actor_type_pro;
		}
	}

	if( delay_data2 >= SWAP_DELAY2 )
	{
		//engine_gamer_manager_frame();
		if( screen_type_title == screen || screen_type_start == screen )
		{
			bonus_tile++;
			if( bonus_tile > tile_type_bonusD )
			{
				bonus_tile = tile_type_bonusA;
			}

			// TODO store this or inject!
			engine_option_manager_draw_bonus( distance );
			// TODO store this or inject!

			engine_option_manager_draw_candy( distance );
		}

		delay_data2 = 0;
	}

	if( delay_data3 >= SWAP_DELAY3 )
	{
		engine_gamer_manager_frame();
		delay_data3 = 0;
	}
}

void engine_option_manager_clear()
{
	//unsigned char x[ NUM_DIRECTIONS ] = { 2, 14, 2, 14 };
	//unsigned char y[ NUM_DIRECTIONS ] = { 0, 0, 1, 1 };
	//unsigned char idx;
	//for( idx = 0; idx < NUM_DIRECTIONS; idx++ )
	//{
	//	engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + x[ idx ], TEXT4_Y + y[ idx ] );
	//}
	engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + 2, TEXT4_Y + 0 );
	engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + 14, TEXT4_Y + 0 );
	engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + 2, TEXT4_Y + 1 );
	engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + 14, TEXT4_Y + 1 );
}

void engine_option_manager_draw_actor( unsigned index )
{
	unsigned x, y;
	unsigned enemy;

	x = value_x[ 0 ] * 8;
	y = value_y[ 0 ] * 8;

	// Render all sprites.
	engine_gamer_manager_draws( x, y );

	x = value_x[ 2 ] * 8 + ( index * 8 );
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		y = value_y[ enemy ] * 8;
		engine_enemy_manager_draws( enemy, x, y );
	}
}

void engine_option_manager_text_kid( unsigned index )
{
	unsigned char x = leftside - index;

	// Candy Kid.
	engine_locale_manager_draw_text( location + 0, x + 0, value_y[ 0 ] + 0 );
	engine_locale_manager_draw_text( location + 1, x + 1, value_y[ 0 ] + 1 );
}

void engine_option_manager_text_kid_no( unsigned index, unsigned char image )
{
	unsigned char x = leftside - index;

	// Kid #.
	engine_locale_manager_draw_text( location + 6 + image, x + 1, value_y[ 0 ] + 1 );
}

void engine_option_manager_text_enemy()
{
	unsigned char idx;
	unsigned char loc = 25;

	// Enemy: Pro / Adi / Suz.
	for( idx = 0; idx < MAX_ENEMIES; idx++ )
	{
		engine_locale_manager_draw_text( loc, value_x[ 3 ] + 0, value_y[ idx ] + 0 );
		engine_locale_manager_draw_text( loc + idx + 1, value_x[ 3 ] + 1, value_y[ idx ] + 1 );
	}

	// Build version is on each "intro" screen so draw it here!
	engine_locale_manager_draw_text( 0, SCREEN_TILE_LEFT + 24, BOTT_TEXT_Y );
}

void engine_option_manager_text_enemy_no( unsigned enemy, unsigned char image )
{
	engine_locale_manager_draw_text( location + 8 + ( enemy * 2 ) + image, value_x[ 3 ] + 1, value_y[ enemy ] + 1 );
}

void engine_option_manager_text_start( unsigned char mode )
{
	engine_locale_manager_draw_text( location + 3 + mode, value_x[ 1 ] + 2, TEXT4_Y + 0 );
	engine_locale_manager_draw_text( location + 5, value_x[ 1 ] + 2, TEXT4_Y + 1 );
}

void engine_option_manager_draw_bonus( unsigned index )
{
	unsigned char value_data = engine_score_manager_get_bonus( bonus_tile );
	unsigned char x = leftside - index;

	engine_tile_manager_draw_bonus( bonus_tile, value_x[ 0 ] + 0, value_y[ 1 ] + 0, 1 );
	engine_font_manager_draw_data( value_data, value_x[ 1 ] + 1, value_y[ 1 ] + 0 );

	// PTS.
	engine_font_manager_draw_text( "0 ", x + 3, value_y[ 1 ] + 0 );
	engine_locale_manager_draw_text( location + 2, x, value_y[ 1 ] + 1 );
}

void engine_option_manager_draw_candy( unsigned index )
{
	unsigned char x = leftside - index;
	engine_tile_manager_main_candy( value_x[ 0 ] + 0, value_y[ 2 ] + 0 );

	// PTS.
	engine_font_manager_draw_text( " 10  ", x, value_y[ 2 ] + 0 );
	engine_locale_manager_draw_text( location + 2, x, value_y[ 2 ] + 1 );
}


void engine_option_manager_text_tree( unsigned char index, unsigned char type )
{
	unsigned char x = leftside - index;
	engine_locale_manager_draw_text( location + 14 + type + 1, x + 0, value_y[ 1 ] + 0 );
	engine_locale_manager_draw_text( location + 14, x + 0, value_y[ 1 ] + 1 );
}
void engine_option_manager_text_exit( unsigned char index, unsigned char type )
{
	unsigned char x = leftside - index;
	engine_locale_manager_draw_text( location + 17, x + 0, value_y[ 2 ] + 0 );
	engine_locale_manager_draw_text( location + 17 + type + 1, x + 0, value_y[ 2 ] + 1 );
}


void engine_option_manager_option_tree( unsigned char type )
{
	engine_tile_manager_draw_trees( type, value_x[ 0 ], value_y[ 1 ] );
}
void engine_option_manager_option_exit()
{
	engine_font_manager_draw_text( "EX", value_x[ 0 ], value_y[ 2 ] + 0 );
	engine_font_manager_draw_text( "IT", value_x[ 0 ], value_y[ 2 ] + 1 );
}

void engine_option_manager_text_other()
{
	engine_locale_manager_draw_text( 12, value_x[ 0 ] + 2, value_y[ 3 ] + 0 );
	engine_locale_manager_draw_text( 13, value_x[ 0 ] + 2, value_y[ 3 ] + 1 );

	engine_locale_manager_draw_text( location + 20, value_x[ 2 ], value_y[ 3 ] + 0 );
}

void engine_option_manager_option_world( unsigned char world )
{
	engine_font_manager_draw_text( locale_object_number[ world ], value_x[ 1 ] + 3, value_y[ 3 ] + 0 );
}
void engine_option_manager_option_round( unsigned char round )
{
	engine_font_manager_draw_text( locale_object_number[ round ], value_x[ 1 ] + 3, value_y[ 3 ] + 1 );
}
void engine_option_manager_option_diff( unsigned char diff )
{
	engine_locale_manager_draw_text( 8 + diff, value_x[ 3 ] + 1, value_y[ 3 ] + 1 );
}