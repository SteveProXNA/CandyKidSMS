#include "board_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "locale_manager.h"
#include "mask_manager.h"
#include "state_manager.h"
#include "tile_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\object\board_object.h"
#include <stdio.h>

#define BOT_SIDE_Y		22
#define MID_SIDE_X		22
#define RGT_SIDE_X		28

#define TOP_EXIT_Y		6
#define BOT_EXIT_Y		16

#define TOP2_EXIT_Y		3
#define BOT2_EXIT_Y		8


void engine_board_manager_border( unsigned char index )
{
	struct_state_object *st = &global_state_object;
	unsigned char type = st->state_object_trees_type;
	unsigned char wide;
	unsigned char rght;
	unsigned char left;
	unsigned char midd;
	unsigned char loop;
	
	wide = board_object_wide[ index ];
	midd = board_object_midd[ index ];
	left = board_object_left[ index ];
	for( loop = 0; loop < wide; loop++ )
	{
		if( left == loop || midd == loop )
		{
			if( exit_type_public == st->state_object_exits_type )
			{
				continue;;
			}
		}

		engine_tile_manager_draw_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X + loop * 2, TOP_SIDE_Y );
		engine_tile_manager_draw_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X + loop * 2, BOT_SIDE_Y );
	}

	rght = board_object_rght[ index ];
	for( loop = 1; loop < SCREEN_TILE_HIGH - 1; loop++ )
	{
		if( TOP2_EXIT_Y == loop || BOT2_EXIT_Y == loop )
		{
			if( exit_type_public == st->state_object_exits_type )
			{
				continue;;
			}
		}

		engine_tile_manager_draw_trees( type, SCREEN_TILE_LEFT + LFT_SIDE_X, TOP_SIDE_Y + loop * 2 );
		engine_tile_manager_draw_trees( type, SCREEN_TILE_LEFT + rght, TOP_SIDE_Y + loop * 2 );
	}
}

void engine_board_manager_toggle()
{
	struct_state_object *st = &global_state_object;
	unsigned char index;
	unsigned char x, y;

	for( index = 0; index < 8; index++ )
	{
		x = board_object_exitX[ index ] + SCREEN_TILE_LEFT;
		y = board_object_exitY[ index ];

		if( exit_type_public == st->state_object_exits_type )
		{
			engine_tile_manager_draw_blank( x, y );
		}
		else
		{
			engine_tile_manager_draw_trees( st->state_object_trees_type, x, y );
		}
	}
}



// This is the function that draws opaque tile to hide Kid when moving through exit!
void engine_board_manager_side_tile()
{
	engine_tile_manager_draw_sides( SCREEN_TILE_LEFT - 2, TOP_EXIT_Y );
	engine_tile_manager_draw_sides( SCREEN_TILE_LEFT - 2, BOT_EXIT_Y );

	engine_tile_manager_draw_sides( TREE_COLS * 2 + SCREEN_TILE_LEFT, BOT_EXIT_Y );
	engine_tile_manager_draw_sides( TREE_COLS * 2 + SCREEN_TILE_LEFT, TOP_EXIT_Y );
}

void engine_board_manager_midd_text()
{
	struct_state_object *st = &global_state_object;
	unsigned char type = st->state_object_trees_type;
	unsigned char loop;

	for( loop = 0; loop < 6; loop++ )
	{
		engine_tile_manager_funk_trees( SCREEN_TILE_LEFT + LFT_SIDE_X + 6 + loop * 2, TOP_SIDE_Y + 8 );
		engine_tile_manager_funk_trees( SCREEN_TILE_LEFT + LFT_SIDE_X + 6 + loop * 2, TOP_SIDE_Y + 14 );
	}

	engine_tile_manager_funk_trees( SCREEN_TILE_LEFT + LFT_SIDE_X + 6, TOP_SIDE_Y + 10 );
	engine_tile_manager_funk_trees( SCREEN_TILE_LEFT + LFT_SIDE_X + 6, TOP_SIDE_Y + 12 );
	engine_tile_manager_funk_trees( SCREEN_TILE_LEFT + LFT_SIDE_X + 16, TOP_SIDE_Y + 10 );
	engine_tile_manager_funk_trees( SCREEN_TILE_LEFT + LFT_SIDE_X + 16, TOP_SIDE_Y + 12 );

	for( loop = 0; loop < 4; loop++ )
	{
		engine_font_manager_draw_text( LOCALE_BLANK_SIZE8, SCREEN_TILE_LEFT + LFT_SIDE_X + 8, TOP_SIDE_Y + 10 + loop );
	}
}