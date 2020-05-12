#include "level_manager.h"
#include "global_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "mask_manager.h"
#include "state_manager.h"
#include "tile_manager.h"
#include "..\object\board_object.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"
#include <stdlib.h>

#define CRLF	2				// char
#define CR		'\r'			// 0x0d
#define LF		'\n'			// 0x0a

// Global variable.
struct_level_object global_level_object;

// Private helper methods.
static void load_level( const unsigned char *data, const unsigned char size, const unsigned char bank, unsigned char mult );
//static void draw_level( unsigned char beg_row, unsigned char end_row, unsigned char beg_col, unsigned char end_col );
static void draw_tiles( unsigned char x, unsigned char y );
static unsigned char test_direction( unsigned char x, unsigned char y, unsigned char input_direction );

void engine_level_manager_clear()
{
	unsigned char row, col;
	unsigned char index;

	for( row = 0; row < MAX_ROWS; row++ )
	{
		for( col = 0; col < MAX_COLS; col++ )
		{
			index = ( row + 2 ) * MAZE_COLS + ( col + 2 );
			level_object_tiles_array[ index ] = tile_type_blank;
		}
	}
}

void engine_level_manager_load_level( const unsigned char world, const unsigned char round )
{
	unsigned char halve;
	unsigned char level;
	unsigned char index;
	unsigned char mult;

	halve = TOT_WORLDS / 2 * MAX_ROUNDS;
	level = world * MAX_ROUNDS + round;
	index = 0;

	mult = ( level >= MULTIPLIER_LEVEL ) + 1;
	if( level >= halve )
	{
		index = level - halve;
	}
	else
	{
		index = level;
	}

	devkit_SMS_mapROMBank( FIXED_BANK );
	if( level < halve )
	{
		const unsigned char *data = level_object_AAdata[ index ];
		const unsigned char size = level_object_AAsize[ index ];
		const unsigned char bank = level_object_AAbank[ index ];
		load_level( data, size, bank, mult );
	}
	else
	{
		const unsigned char *data = level_object_BBdata[ index ];
		const unsigned char size = level_object_BBsize[ index ];
		const unsigned char bank = level_object_BBbank[ index ];
		load_level( data, size, bank, mult );
	}
}

void engine_level_manager_temp_level( unsigned char tileX, unsigned char tileY, unsigned char tile_type )
{
	// Surround home tile with "dummy" tile so not to get chosen during oneup randomize for boss battle.
	struct_level_object *lo = &global_level_object;
	unsigned char row, col;
	unsigned char index;

	for( row = 0; row < 2; row++ )
	{
		for( col = 0; col < 3; col++ )
		{
			index = ( tileY + row ) * MAZE_COLS + ( tileX + col );
			level_object_tiles_array[ index ] = tile_type;
		}
	}
}

void engine_level_manager_load_extra( unsigned char quantity, unsigned char tile_type )
{
	struct_level_object *lo = &global_level_object;
	unsigned char row, col;
	unsigned char index;
	unsigned char tiles;
	unsigned char loops;

	lo->level_object_oneup_count = 0;
	for( loops = 0; loops < quantity; loops++ )
	{
		while( 1 )
		{
			row = rand() % MAX_ROWS;
			col = rand() % MAX_COLS;

			// TODO delete testing...
			//if( 0 == loops )
			//{
			//	row = 4;
			//	col = 4;
			//}

			// TODO remove
			//row = 0;
			//col = 0;

			// TODO calculate rectangle around boss home so no candy drawn there!
		//	//// Ensure no 
		//	//if( !( col == board_object_homeX[ 0 ] - 2 && row == board_object_homeY[ 0 ] - 2 ) &&
		//	//	!( col == board_object_homeX[ 1 ] - 2 && row == board_object_homeY[ 1 ] - 2 ) &&
		//	//	!( col == board_object_homeX[ 2 ] - 2 && row == board_object_homeY[ 2 ] - 2 ) &&
		//	//	!( col == board_object_homeX[ 3 ] - 2 && row == board_object_homeY[ 3 ] - 2 ) )
		//	//{

			index = ( row + 2 ) * MAZE_COLS + ( col + 2 );
			tiles = level_object_tiles_array[ index ];
			if( tile_type_blank == tiles )
			{
				break;
			}
		}

		level_object_tiles_array[ index ] = tile_type;
		if( tile_type_oneup == tile_type )
		{
			lo->level_object_oneup_count++;
		}
		
	}

	//col = 0;
	//loops = 0;
	//index = ( row + 2 ) * MAZE_COLS + ( col + 2 );
	//level_object_tiles_array[ index ] = tile_type_oneup;
}

void engine_level_manager_directions()
{
	unsigned char row, col;
	unsigned int index;
	unsigned char test_type;
	unsigned char direction;

	// Set each tile directions available.
	for( row = 0; row < MAX_ROWS; row++ )
	{
		for( col = 0; col < MAX_COLS; col++ )
		{
			direction = engine_level_manager_test_direction( ( row + 2 ), ( col + 2 ) );

			index = ( row + 2 ) * MAZE_COLS + ( col + 2 );
			test_type = level_object_tiles_array[ index ];

			engine_function_manager_convertNibblesToByte( direction, test_type, &test_type );
			level_object_tiles_array[ index ] = test_type;
		}
	}
}

// TODO delete
//void engine_level_manager_update_level( const unsigned char round, unsigned char *actor_mover, unsigned char *actor_tileZ )
//{
//	struct_level_object *lo = &global_level_object;
//	struct_state_object *st = &global_state_object;
//	unsigned char actor;
//	unsigned char mover;
//	unsigned char index;
//	unsigned char tileX;
//	unsigned char tileY;
//	unsigned char tiles;
//	unsigned char tile_type;
//	unsigned char upper_nibble;
//	unsigned char lower_nibble;
//
//	// Count all available home tiles: Kid, Pro, Adi, Suz
//	// Kid always moves so means that will be at least 1x.
//	tiles = 0;
//	for( actor = 0; actor < MAX_ACTORS; actor++ )
//	{
//		mover = actor_mover[ actor ];
//		if( mover )
//		{
//			tiles++;
//			continue;
//		}
//
//		// Enemy is idle this level so blank out tile.
//		index = actor_tileZ[ actor ];
//		engine_function_manager_convertZtoXY( MAZE_ROWS, index, &tileX, &tileY );
//		tile_type = engine_level_manager_get_tile_type( tileX, tileY, direction_type_none, offset_type_none );
//
//		if( tile_type_bonusA == tile_type || tile_type_bonusB == tile_type || tile_type_bonusC == tile_type || tile_type_bonusD == tile_type )
//		{
//			lo->level_object_bonus_count--;
//		}
//		if( tile_type_candy == tile_type )
//		{
//			lo->level_object_candy_count--;
//		}
//
//		tile_type = engine_level_manager_get_next_tile( tileX, tileY, direction_type_none, offset_type_none );
//		engine_function_manager_convertByteToNibbles( tile_type, &upper_nibble, &lower_nibble );
//		lower_nibble = tile_type_blank;
//		engine_function_manager_convertNibblesToByte( upper_nibble, lower_nibble, &tile_type );
//		level_object_tiles_array[ index ] = tile_type;
//	}
//
//	// Every fifth level award freeman tile if not invincible.
//	if( st->state_object_localcheat )
//	{
//		return;
//	}
//	if( 0 != ( round + 1 ) % 5 )
//	{
//		return;
//	}
//
//	// However, flip coin if can have free man candy on difficult hard.
//	if( diff_type_hard == st->state_object_difficulty )
//	{
//		
//		if( 0 != rand() % 2 )
//		{
//			return;
//		}
//	}
//
//	mover = rand() % tiles;
//	index = actor_tileZ[ mover ];
//	engine_function_manager_convertZtoXY( MAZE_ROWS, index, &tileX, &tileY );
//	tile_type = engine_level_manager_get_tile_type( tileX, tileY, direction_type_none, offset_type_none );
//
//	if( tile_type_bonusA == tile_type || tile_type_bonusB == tile_type || tile_type_bonusC == tile_type || tile_type_bonusD == tile_type )
//	{
//		lo->level_object_bonus_count--;
//	}
//	if( tile_type_candy == tile_type )
//	{
//		lo->level_object_candy_count--;
//	}
//
//	tile_type = engine_level_manager_get_next_tile( tileX, tileY, direction_type_none, offset_type_none );
//	engine_function_manager_convertByteToNibbles( tile_type, &upper_nibble, &lower_nibble );
//	lower_nibble = tile_type_oneup;
//	engine_function_manager_convertNibblesToByte( upper_nibble, lower_nibble, &tile_type );
//	level_object_tiles_array[ index ] = tile_type;
//}

void engine_level_manager_draw_level()
{
	unsigned char row, col;
	for( row = 0; row < MAX_ROWS; row++ )
	{
		for( col = 0; col < MAX_COLS; col++ )
		{
			if( row >= 3 && row < 7 && col >= 2 && col < 8 )
			{
				continue;
			}

			draw_tiles( col, row );
		}
	}
}
void engine_level_manager_draw_middle()
{
	unsigned char row, col;
	for( row = 3; row < 7; row++ )
	{
		for( col = 2; col < 8; col++ )
		{
			draw_tiles( col, row );
		}
	}
}



void engine_level_manager_beat_level( const unsigned char *data, const unsigned char size, const unsigned char bank )
{
	load_level( data, size, bank, 1 );
}

void engine_level_manager_blank_tile( unsigned char index )
{
	unsigned char upper_nibble;
	unsigned char lower_nibble;

	unsigned char tile_type = level_object_tiles_array[ index ];

	engine_function_manager_convertByteToNibbles( tile_type, &upper_nibble, &lower_nibble );
	lower_nibble = tile_type_blank;
	engine_function_manager_convertNibblesToByte( upper_nibble, lower_nibble, &tile_type );
	level_object_tiles_array[ index ] = tile_type;
}

unsigned char engine_level_manager_get_collision( unsigned char x, unsigned char y, unsigned char direction, unsigned char offset )
{
	// Returns collision type for next (x, y) tile offset from direction.
	unsigned char collision;
	unsigned char upper_nibble;
	unsigned char lower_nibble;

	unsigned char tile = engine_level_manager_get_next_tile( x, y, direction, offset );
	engine_function_manager_convertByteToNibbles( tile, &upper_nibble, &lower_nibble );

	collision = COLL_TYPE_MASK == ( tile & COLL_TYPE_MASK );
	return collision;
}
unsigned char engine_level_manager_get_direction( unsigned char x, unsigned char y, unsigned char direction, unsigned char offset )
{
	// Returns all directions for next (x, y) tile offset from direction.
	unsigned char upper_nibble;
	unsigned char lower_nibble;

	unsigned char tile = engine_level_manager_get_next_tile( x, y, direction, offset );
	engine_function_manager_convertByteToNibbles( tile, &upper_nibble, &lower_nibble );

	return upper_nibble;
}
unsigned char engine_level_manager_get_tile_type( unsigned char x, unsigned char y, unsigned char direction, unsigned char offset )
{
	// Returns draw tile type for next (x, y) tile offset from direction.
	unsigned char tile_type;
	unsigned char upper_nibble;
	unsigned char lower_nibble;

	unsigned char tile = engine_level_manager_get_next_tile( x, y, direction, offset );
	engine_function_manager_convertByteToNibbles( tile, &upper_nibble, &lower_nibble );

	tile_type = lower_nibble;
	if( COLL_TYPE_MASK == ( tile_type & COLL_TYPE_MASK ) )
	{
		tile_type = lower_nibble ^ COLL_TYPE_MASK;
	}

	return tile_type;
}
unsigned char engine_level_manager_get_next_tile( unsigned char x, unsigned char y, unsigned char direction, unsigned char offset )
{
	unsigned char index;

	// Note: x and y can never go out-of-bounds: if gamer in exits then there will be no collision checks.
	if( direction_type_upxx == direction )
	{
		y -= offset;
	}
	else if( direction_type_down == direction )
	{
		y += offset;
	}
	else if( direction_type_left == direction )
	{
		x -= offset;
	}
	else if( direction_type_rght == direction )
	{
		x += offset;
	}

	engine_function_manager_convertXYtoZ( MAZE_ROWS, x, y, &index );
	return level_object_tiles_array[ index ];
}

void engine_level_manager_get_next_index( unsigned char *x, unsigned char *y, unsigned char direction, signed char offset )
{
	// Note: x and y can never go out-of-bounds: if gamer in exits then there will be no collision checks.
	if( direction_type_upxx == direction )
	{
		*y -= offset;
	}
	else if( direction_type_down == direction )
	{
		*y += offset;
	}
	else if( direction_type_left == direction )
	{
		*x -= offset;
	}
	else if( direction_type_rght == direction )
	{
		*x += offset;
	}
}


// TODO don't believe this will be needed so could delete at the end...
unsigned char engine_level_manager_test_direction( unsigned char row, unsigned char col )
{
	unsigned char direction_type = direction_type_none;

	// Check UP.
	if( 0 != row )
	{
		unsigned char test_type = test_direction( ( col + 0 ), ( row - 1 ), direction_type_upxx );
		direction_type |= test_type;
	}

	// Check DOWN.
	if( MAZE_ROWS - 1 != row )
	{
		unsigned char test_type = test_direction( ( col + 0 ), ( row + 1 ), direction_type_down );
		direction_type |= test_type;
	}

	// Check LEFT.
	if( 0 != col )
	{
		unsigned char test_type = test_direction( ( col - 1 ), ( row + 0 ), direction_type_left );
		direction_type |= test_type;
	}

	// Check RIGHT.
	if( MAZE_COLS - 1 != col )
	{
		unsigned char test_type = test_direction( ( col + 1 ), ( row + 0 ), direction_type_rght );
		direction_type |= test_type;
	}

	return direction_type;
}

// Private helper methods.
static void load_level( const unsigned char *data, const unsigned char size, const unsigned char bank, unsigned char mult )
{
	struct_level_object *lo = &global_level_object;
	const unsigned char *o = data;
	unsigned char row, col;
	unsigned char tile_data;

	unsigned char index;
	unsigned char tile_type;
	unsigned char coll_type;
	//unsigned char test_type;
	//unsigned char direction;

	unsigned char load_cols;
	unsigned char draw_cols;
	load_cols = size / MAX_ROWS;
	draw_cols = load_cols - CRLF;
	lo->level_object_bonus_count = 0;
	lo->level_object_candy_count = 0;
	
	lo->level_object_multiplier = mult;

	mult = 0;
	devkit_SMS_mapROMBank( bank );
	for( row = 0; row < MAX_ROWS; row++ )
	{
		for( col = 0; col < load_cols; col++ )
		{
			tile_data = *o;
			if( !( tile_data == CR || tile_data == LF ) )
			{
				engine_tile_manager_load_tile( &tile_type, tile_data );
				index = ( row + 2 ) * MAZE_COLS + ( col + 2 );

				if( tile_type_bonusA == tile_type || tile_type_bonusB == tile_type || tile_type_bonusC == tile_type || tile_type_bonusD == tile_type )
				{
					lo->level_object_bonus_count++;
				}
				if( tile_type_candy == tile_type )
				{
					lo->level_object_candy_count++;
				}

				engine_tile_manager_load_coll( &coll_type, tile_data );
				if( coll_type_block == coll_type )
				{
					tile_type |= COLL_TYPE_MASK;
				}

				level_object_tiles_array[ index ] = tile_type;
			}

			o++;
		}
	}

	// Set each tile directions available.
	//for( row = 0; row < MAX_ROWS; row++ )
	//{
	//	for( col = 0; col < MAX_COLS; col++ )
	//	{
	//	//	if( 3 == row && 1 == col )
	//	//	{
	//	//		index = 0;
	//	//	}
	//		direction = engine_level_manager_test_direction( ( row + 2 ), ( col + 2 ) );

	//		index = ( row + 2 ) * MAZE_COLS + ( col + 2 );
	//		test_type = level_object_tiles_array[ index ];

	//		engine_function_manager_convertNibblesToByte( direction, test_type, &test_type );
	//		level_object_tiles_array[ index ] = test_type;
	//	}
	//}
}

static void draw_tiles( unsigned char x, unsigned char y )
{
	struct_level_object *lo = &global_level_object;
	unsigned char index;
	unsigned char tile;

	index = ( y + 2 ) * MAZE_COLS + ( x + 2 );
	tile = level_object_tiles_array[ index ];
	engine_tile_manager_draw_tile( tile, SCREEN_TILE_LEFT + ( x + 1 ) * 2, ( y + 1 ) * 2, lo->level_object_multiplier );
}

static unsigned char test_direction( unsigned char x, unsigned char y, unsigned char input_direction )
{
	unsigned char index;
	unsigned char tile;
	unsigned char coll;
	unsigned char test_type = direction_type_none;

	index = y * MAZE_COLS + x;
	tile = level_object_tiles_array[ index ];

	coll = COLL_TYPE_MASK == ( tile & COLL_TYPE_MASK );
	if( coll_type_empty == coll )
	{
		test_type = input_direction;
	}

	return test_type;
}
