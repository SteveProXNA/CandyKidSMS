#include "start_screen.h"
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
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"
#include <stdlib.h>

static void display_cursor();
static unsigned char event_stage;
static unsigned char distance;
static unsigned char cursorY[ 2 ] = { TEXT4_Y + 0, TEXT4_Y + 1 };
static unsigned char cursor;

void screen_start_screen_init()
{
	cursor = 0;
}

void screen_start_screen_load()
{
	struct_state_object *st = &global_state_object;

	// Clear menu area first.
	engine_option_manager_clear();
	distance = menu_type_double;
	engine_option_manager_draw_bonus( distance );
	engine_option_manager_draw_candy( distance );

	// Draw all generic actor text.
	engine_option_manager_text_kid( distance );
	engine_option_manager_text_enemy();

	// Draw NEW GAME or CONTINUE...
	engine_option_manager_text_start( st->state_object_availables );
	display_cursor();

	engine_delay_manager_load( SOUND_SCREEN_DELAY );
	event_stage = event_stage_start;

	st->state_object_next_screen = screen_type_init;
	st->state_object_curr_screen = screen_type_start;
}

void screen_start_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	struct_hack_object *ho = &global_hack_object;
	unsigned char input[ 2 ] = { 0, 0 };
	unsigned char delay;

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
			*screen_type = st->state_object_next_screen;
		}

		return;
	}


	input[ 0 ] = engine_input_manager_hold( input_type_up );
	input[ 1 ] = engine_input_manager_hold( input_type_down );
	if( input[ 0 ] || input[ 1 ] )
	{
		cursor = 1 - cursor;
		display_cursor();
	}

	input[ 0 ] = engine_input_manager_hold( input_type_fire1 );
	if( input[ 0 ] )
	{
		if( 0 == cursor )
		{
			st->state_object_next_screen = screen_type_init;
		}
		else if( 1 == cursor )
		{
			st->state_object_next_screen = screen_type_option;
		}

		event_stage = event_stage_pause;
		if( !ho->hack_object_delay_test )
		{
			engine_audio_manager_sfx_play( sfx_type_accept );
		}

		return;
	}

	input[ 1 ] = engine_input_manager_hold( input_type_fire2 );
	if( input[ 1 ] )
	{
		event_stage = event_stage_pause;
		st->state_object_next_screen = screen_type_title;
		engine_audio_manager_sfx_play( sfx_type_reset );
		return;
	}

	rand();
}

static void display_cursor()
{
	engine_font_manager_draw_text( LOCALE_SELECT_SPACES, SCREEN_TILE_LEFT + 8, cursorY[ 0 ] );
	engine_font_manager_draw_text( LOCALE_SELECT_SPACES, SCREEN_TILE_LEFT + 8, cursorY[ 1 ] );
	engine_font_manager_draw_text( LOCALE_SELECT_ARROWS, SCREEN_TILE_LEFT + 8, cursorY[ cursor ] );
}