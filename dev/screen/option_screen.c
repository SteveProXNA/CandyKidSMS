#include "option_screen.h"
#include "..\engine\asm_manager.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\hack_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\main_manager.h"
#include "..\engine\option_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\storage_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"

static void display_cursor( unsigned char type );
static void toggle_kid();
static void toggle_enemy( unsigned char enemy );
static void toggle_trees();
static void toggle_exits();
static void toggle_world();
static void toggle_round();
static void toggle_diff();

static unsigned char event_stage;
static unsigned char distance;
static unsigned char cursorsX[ 2 ] = { OPTION_X + 2, OPTION_X + 15 };
static unsigned char cursorsY[ 5 ] = { OPTION_Y + 1, OPTION_Y + 4, OPTION_Y + 7, OPTION_Y + 10, OPTION_Y + 11 };
static unsigned char cursorX;
static unsigned char cursorY;
static unsigned char lastVert;

void screen_option_screen_init()
{
	cursorX = 0;
	cursorY = 0;
	lastVert = 0;
}

void screen_option_screen_load()
{
	struct_state_object *st = &global_state_object;
	struct_gamer_object *go = &global_gamer_object;
	struct_enemy_object *eo;
	unsigned char enemy;

	// Clear menu area first.
	engine_option_manager_clear();
	distance = menu_type_double;

	engine_delay_manager_load( SOUND_SCREEN_DELAY );

	engine_option_manager_option_tree( st->state_object_trees_type );
	engine_option_manager_option_exit();

	// Draw Kid#, Pro#, Adi#, Suz#
	engine_option_manager_text_kid_no( distance, go->image );
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		engine_option_manager_text_enemy_no( enemy, eo->image );
	}

	// Draw tree options.
	engine_option_manager_text_tree( distance, st->state_object_trees_type );

	// Draw exit options.
	engine_option_manager_text_exit( distance, st->state_object_exits_type );

	// Draw level + difficulty text.
	engine_option_manager_text_other();

	// Draw world + round data.
	engine_option_manager_option_world( st->state_object_world_data );
	engine_option_manager_option_round( st->state_object_round_data );

	// Draw difficulty.
	engine_option_manager_option_diff( st->state_object_difficulty );


	display_cursor( cursor_type_arrows );
	event_stage = event_stage_start;

	st->state_object_next_screen = screen_type_start;
	st->state_object_curr_screen = screen_type_option;
}

void screen_option_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	struct_hack_object *ho = &global_hack_object;
	unsigned char input[ 2 ] = { 0, 0 };
	unsigned char delay;
	unsigned char skip = 0;

	engine_option_manager_draw_actor( distance );
	if( !ho->hack_object_delay_test )
	{
		engine_option_manager_update( st->state_object_curr_screen );
	}


	// Set the current screen first.
	*screen_type = st->state_object_curr_screen;


	// Enable slight pause for movement.
	if( event_stage_pause == event_stage )
	{
		delay = engine_delay_manager_update();
		if( delay )
		{
			display_cursor( cursor_type_spaces );
			*screen_type = st->state_object_next_screen;
		}

		return;
	}


	input[ 0 ] = engine_input_manager_hold( input_type_up );
	input[ 1 ] = engine_input_manager_hold( input_type_down	 );
	if( input[ 0 ] || input[ 1 ] )
	{
		skip = 1 == cursorX;
		display_cursor( cursor_type_spaces );
		if( input[ 0 ] )
		{
			lastVert = 0;
			if( 0 == cursorY )
			{
				cursorY = 4;
			}
			else
			{
				if( skip && 4 == cursorY )
				{
					cursorY--;
				}

				cursorY--;
			}
		}
		if( input[ 1 ] )
		{
			lastVert = 1;
			if( 4 == cursorY )
			{
				cursorY = 0;
			}
			else
			{
				if (skip && 2 == cursorY )
				{
					cursorY++;
				}
				
				cursorY++;
			}
		}

		display_cursor( cursor_type_arrows );
	}
	else
	{
		input[ 0 ] = engine_input_manager_hold( input_type_left );
		input[ 1 ] = engine_input_manager_hold( input_type_right );
		if( input[ 0 ] || input[ 1 ] )
		{
			display_cursor( cursor_type_spaces );

			// Special case
			if( 0 == cursorX && 3 == cursorY )
			{
				if( 0 == lastVert )
				{
					cursorY--;
				}
				else
				{
					cursorY++;
				}
			}

			cursorX = 1 - cursorX;
			display_cursor( cursor_type_arrows );
		}
	}


	input[ 0 ] = engine_input_manager_hold( input_type_fire1 );
	if( input[ 0 ] )
	{
		if( 0 == cursorX )
		{
			if( 0 == cursorY )
			{
				toggle_kid();
			}
			else if( 1 == cursorY )
			{
				toggle_trees();
			}
			else if( 2 == cursorY )
			{
				toggle_exits();
			}
			else if( 3 == cursorY )
			{
				toggle_world();
			}
			else if( 4 == cursorY )
			{
				toggle_round();
			}
		}
		if( 1 == cursorX )
		{
			if( 4 == cursorY )
			{
				toggle_diff();
			}
			else
			{
				toggle_enemy( cursorY );
			}
		}
	}


	input[ 1 ] = engine_input_manager_hold( input_type_fire2 );
	if( input[ 1 ] )
	{
		// Save game state to SRAM when game over.
		engine_main_manager_save();

		event_stage = event_stage_pause;
		engine_audio_manager_sfx_play( sfx_type_reset );
		return;
	}
}

static void display_cursor( unsigned char type )
{
	unsigned char x = cursorsX[ cursorX ];
	if( 0 == cursorX && ( 3 == cursorY || 4 == cursorY ) )
	{
		x -= 2;
	}

	if( cursor_type_arrows == type )
	{
		engine_font_manager_draw_text( LOCALE_SELECT_ARROWS, x, cursorsY[ cursorY ] );
	}
	else
	{
		engine_font_manager_draw_text( LOCALE_SELECT_SPACES, x, cursorsY[ cursorY ] );
	}
}

static void toggle_kid()
{
	struct_gamer_object *go = &global_gamer_object;
	engine_gamer_manager_image();
	engine_option_manager_text_kid_no( distance, go->image );
}
static void toggle_enemy( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	engine_enemy_manager_image( enemy );
	engine_option_manager_text_enemy_no( enemy, eo->image );
}
static void toggle_trees()
{
	struct_state_object *st = &global_state_object;
	st->state_object_trees_type = 1 - st->state_object_trees_type;
	engine_board_manager_border( border_type_main );
	engine_option_manager_text_tree( distance, st->state_object_trees_type );
	engine_option_manager_option_tree( st->state_object_trees_type );
}
static void toggle_exits()
{
	struct_state_object *st = &global_state_object;
	st->state_object_exits_type = 1 - st->state_object_exits_type;
	engine_option_manager_text_exit( distance, st->state_object_exits_type );
	engine_board_manager_toggle();
}
static void toggle_world()
{
	struct_state_object *st = &global_state_object;
	st->state_object_world_data++;
	if (st->state_object_world_data >= MAX_WORLDS )
	{
		st->state_object_world_data = 0;
	}

	engine_option_manager_option_world( st->state_object_world_data );
}
static void toggle_round()
{
	struct_state_object *st = &global_state_object;
	st->state_object_round_data++;
	if( st->state_object_round_data >= MAX_ROUNDS )
	{
		st->state_object_round_data = 0;
	}

	engine_option_manager_option_round( st->state_object_round_data );
}
static void toggle_diff()
{
	struct_state_object *st = &global_state_object;
	st->state_object_difficulty = 1 - st->state_object_difficulty;
	engine_option_manager_option_diff( st->state_object_difficulty );
}