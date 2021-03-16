#include "beat_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
//#include "..\engine\command_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\main_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\timer_manager.h"
#include "..\object\audio_object.h"
#include "..\banks\bank6.h"

#define BEAT_SCREEN_DELAY	900

static unsigned char command_index;
static unsigned char command_count;
static unsigned char walking_delta;
static unsigned char walking_count;

unsigned char beat_walking_cmds[] = { direction_type_rght, direction_type_down, direction_type_left, direction_type_upxx };
unsigned char beat_walking_move[] = { 7, 7, 7, 7 };

void screen_beat_screen_load()
{
	struct_state_object *st = &global_state_object;
	const unsigned char *data = beats0000_txt;
	const unsigned char size = beats0000_txt_size;
	const unsigned char bank = beats0000_txt_bank;

	st->state_object_curr_screen = screen_type_beat;
	st->state_object_next_screen = screen_type_begin;

	engine_audio_manager_music_stop();
	engine_delay_manager_load( BEAT_SCREEN_DELAY );

	engine_level_manager_beat_level( data, size, bank );
	engine_level_manager_draw_level();
	
	engine_memo_manager_draw( 21, 22 );
	command_index = 0;
	command_count = 4;
	walking_delta = 0;
	walking_count = 0;

	engine_gamer_manager_load();
	engine_gamer_manager_reset();
	engine_audio_manager_music_play_norepeat( mus_type_beat );
}

void screen_beat_screen_update( unsigned char *screen_type )
{
	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	struct_state_object *st = &global_state_object;
	unsigned char the_direction;
	unsigned char delay;
	unsigned char input;
	unsigned int frame = fo->frame_count;

	delay = engine_delay_manager_update();
	input = engine_input_manager_hold( input_type_fire2 );
	if( delay || input )
	{
		engine_audio_manager_music_stop();
		st->state_object_world_data = 0;
		st->state_object_round_data = 0;

		// Save game state to SRAM when game over.
		engine_main_manager_save();

		*screen_type = st->state_object_next_screen;
		return;
	}

	engine_gamer_manager_draw();


	// Continue...
	frame = fo->frame_count;

	// Move gamer.
	if( direction_type_none != go->direction && lifecycle_type_move == go->lifecycle )
	{
		//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
		engine_gamer_manager_update();
	}
	if( direction_type_none != go->direction && lifecycle_type_idle == go->lifecycle )
	{
		// Check collision.
		engine_gamer_manager_stop();
	}
	// For continuity we want to check if actor can move immediately after stopping.
	if( direction_type_none == go->direction && lifecycle_type_idle == go->lifecycle )
	{
		the_direction = direction_type_none;
		walking_count = 0;

		if( command_index >= command_count )
		{
			command_index = 0;
		}
		
		the_direction = beat_walking_cmds[ command_index ];
		walking_count = beat_walking_move[ command_index ];

		walking_delta++;
		if( walking_delta >= walking_count )
		{
			command_index++;
			walking_delta = 0;
		}

//		engine_command_manager_add( frame, command_type_gamer_mover, the_direction );
		engine_gamer_manager_move( the_direction );
	}


	// Execute all commands for this frame.
//	engine_command_manager_execute( frame );


	*screen_type = st->state_object_curr_screen;
}