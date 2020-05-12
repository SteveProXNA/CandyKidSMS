#include "tile_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "locale_manager.h"
#include "mask_manager.h"
#include "state_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\bank2.h"
#include "..\gfx.h"
#include <stdlib.h>

#define BASE_TILES_OFFSET	26
#define BASE_BLOCK_OFFSET	12
#define BASE_CANDY_OFFSET	52
#define BASE_DEATH_OFFSET	22
#define BASE_GAMER_OFFSET	20

#define MAIN_CANDY_OFFSET	12
#define MAIN_GAMER_OFFSET	24

static void draw_tile( unsigned char offset, unsigned char x, unsigned char y );
static void draw_tile_priority( unsigned char offset, unsigned char x, unsigned char y );
static void main_tile( unsigned char offset, unsigned char x, unsigned char y );
static void comm_tile( const unsigned char *pnt, unsigned char offset, unsigned int priority, unsigned char x, unsigned char y );

void engine_tile_manager_load_tile( unsigned char *tile_type, unsigned char tile_data )
{
	if( '1' == tile_data )
	{
		*tile_type = tile_type_trees;
		return;
	}
	if( '2' == tile_data )
	{
		*tile_type = tile_type_candy;
		return;
	}
	if( '3' == tile_data )
	{
		*tile_type = tile_type_bonusA;
		return;
	}
	if( '4' == tile_data )
	{
		*tile_type = tile_type_bonusB;
		return;
	}
	if( '5' == tile_data )
	{
		*tile_type = tile_type_bonusC;
		return;
	}
	if( '6' == tile_data )
	{
		*tile_type = tile_type_bonusD;
		return;
	}

	*tile_type = tile_type_blank;
}

void engine_tile_manager_load_coll( unsigned char *coll_type, unsigned char tile_data )
{
	if( '1' == tile_data )
	{
		*coll_type = coll_type_block;
		return;
	}

	*coll_type = coll_type_empty;
}

// TODO rename this as is too generic!
void engine_tile_manager_draw_tile( unsigned char tile, unsigned char x, unsigned char y, unsigned char mult )
{
	struct_state_object *st = &global_state_object;
	unsigned char upper_nibble;
	unsigned char lower_nibble;
	unsigned char tile_type;

	engine_function_manager_convertByteToNibbles( tile, &upper_nibble, &lower_nibble );
	tile_type = lower_nibble & TILE_TYPE_MASK;

	if( tile_type_blank == tile_type )
	{
		engine_tile_manager_draw_blank( x, y );
	}
	else if( tile_type_trees == tile_type )
	{
		engine_tile_manager_draw_trees( st->state_object_trees_type, x, y );
	}
	else if( tile_type >= tile_type_bonusA  && tile_type <= tile_type_bonusD )
	{
		//engine_tile_manager_draw_bonus( tile_type, x, y, level_object_multiplier );
		engine_tile_manager_draw_bonus( tile_type, x, y, mult );
	}
	else if( tile_type_candy == tile_type )
	{
		engine_tile_manager_draw_candy( x, y );
	}
	else if( tile_type_oneup == tile_type )
	{
		engine_tile_manager_draw_oneup( x, y );
	}
}

void engine_tile_manager_draw_blank( unsigned char x, unsigned char y )
{
	engine_font_manager_draw_text( LOCALE_SELECT_SPACES, x + 0, y + 0 );
	engine_font_manager_draw_text( LOCALE_SELECT_SPACES, x + 0, y + 1 );
}

void engine_tile_manager_draw_candy( unsigned char x, unsigned char y )
{
	unsigned char type = rand() % MAX_BLOCK_TILES;
	unsigned char offset = type * 2 + BASE_CANDY_OFFSET;
	draw_tile( offset, x, y );
}

void engine_tile_manager_draw_trees( unsigned char type, unsigned char x, unsigned char y )
{
	unsigned char offset = type * 2;
	draw_tile( offset, x, y );
}

void engine_tile_manager_draw_bonus( unsigned char type, unsigned char x, unsigned char y, unsigned char multiplier )
{
	unsigned char offset = ( type - 1 ) * 2;
	//offset += ( level_object_multiplier - 1 ) * 8;
	offset += ( multiplier - 1 ) * 8;
	draw_tile( offset, x, y );
}

void engine_tile_manager_draw_oneup( unsigned char x, unsigned char y )
{
	unsigned char offset = BASE_GAMER_OFFSET;
	draw_tile( offset, x, y );
}

void engine_tile_manager_draw_cross( unsigned char type, unsigned char x, unsigned char y )
{
	unsigned char offset = type * 2 + BASE_DEATH_OFFSET;
	draw_tile( offset, x, y );
}

void engine_tile_manager_draw_sides( unsigned char x, unsigned char y )
{
	unsigned char offset = BASE_BLOCK_OFFSET * 2 + BASE_CANDY_OFFSET;
	draw_tile_priority( offset, x, y );
	//draw_tile( offset, x, y );
}

// Methods used for this main title screen.
void engine_tile_manager_main_title( unsigned char x, unsigned char y )
{
	const unsigned int *pnt = ( const unsigned int * ) main_tiles__tilemap__bin;

	unsigned char i;
	unsigned char j;

	// CANDY KID title is 26 cols * 4 rows of 8x8 tiles.
	for( j = 2; j < 6; j++ )
	{
		for( i = 0; i < 26; i++ )
		{
			devkit_SMS_setNextTileatXY( SCREEN_TILE_LEFT + x + i, y + ( j - 2 ) );
			devkit_SMS_setTile( *pnt + j * 26 + i );
		}
	}
}

void engine_tile_manager_main_candy( unsigned char x, unsigned char y )
{
	unsigned char type = rand() % ( MAX_BLOCK_TILES / 2 );
	unsigned char offset = type * 2 + MAIN_CANDY_OFFSET;
	draw_tile( offset, x, y );
}

void engine_tile_manager_main_gamer( unsigned char x, unsigned char y )
{
	unsigned char offset = MAIN_GAMER_OFFSET;
	draw_tile( offset, x, y );
}

void engine_tile_manager_funk_trees( unsigned char x, unsigned char y )
{
	unsigned char offset = 0;
	draw_tile_priority( offset, x, y );
}

static void draw_tile( unsigned char offset, unsigned char x, unsigned char y )
{
	const unsigned char priority = 0;
	comm_tile( game_tiles__tilemap__bin, offset, priority, x, y );
}

static void draw_tile_priority( unsigned char offset, unsigned char x, unsigned char y )
{
	unsigned int priority = devkit_TILE_PRIORITY() | devkit_TILE_USE_SPRITE_PALETTE();
	comm_tile( game_tiles__tilemap__bin, offset, priority, x, y );
}

static void main_tile( unsigned char offset, unsigned char x, unsigned char y )
{
	const unsigned int priority = 0;
	comm_tile( main_tiles__tilemap__bin, offset, priority, x, y );
}

static void comm_tile( const unsigned char *pnt, unsigned char offset, unsigned int priority, unsigned char x, unsigned char y )
{
	//devkit_SMS_mapROMBank( CONTENT_BANK );
	devkit_SMS_setNextTileatXY( x + 0, y + 0 );	devkit_SMS_setTile( ( *pnt + offset + 0 ) | priority );
	devkit_SMS_setNextTileatXY( x + 1, y + 0 );	devkit_SMS_setTile( ( *pnt + offset + 1 ) | priority );
	devkit_SMS_setNextTileatXY( x + 0, y + 1 );	devkit_SMS_setTile( ( *pnt + offset + BASE_TILES_OFFSET + 0 ) | priority );
	devkit_SMS_setNextTileatXY( x + 1, y + 1 );	devkit_SMS_setTile( ( *pnt + offset + BASE_TILES_OFFSET + 1 ) | priority );
}