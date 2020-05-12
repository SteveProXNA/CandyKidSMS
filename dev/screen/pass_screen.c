#include "pass_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\boss_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\timer_manager.h"

#define PASS_SCREEN_DELAY1	25
#define PASS_SCREEN_DELAY2	250

static void draw_actor();
static void hide_actor();
static void next_level();

static unsigned char event_stage;
static unsigned char perfect;

void screen_pass_screen_load()
{
	struct_score_object *so = &global_score_object;
	struct_state_object *st = &global_state_object;
	struct_level_object *lo = &global_level_object;

	// Draw sprites first.
	draw_actor();
	//engine_enemy_manager_draw();
	//engine_gamer_manager_draw();

	st->state_object_curr_screen = screen_type_pass;
	st->state_object_next_screen = screen_type_load;

	engine_delay_manager_load( PASS_SCREEN_DELAY1 );
	engine_audio_manager_music_stop();

	perfect = 1;
	if( fight_type_enemy == st->state_object_fight_type )
	{
		perfect = ( lo->level_object_bonus_count + lo->level_object_candy_count == so->bonus + so->candy );
	}

	event_stage = event_stage_start;
}

// TODO combine pass + bonus screen
void screen_pass_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char delay;
	unsigned char input;

	if( event_stage_pause == event_stage )
	{
		delay = engine_delay_manager_update();
		input = 0;
		//if( st->state_object_mydebugger )
		//{
			input = engine_input_manager_hold( input_type_fire2 );
		//}
		if( delay || input )
		{
			next_level();
			//engine_state_manager_level();
			engine_audio_manager_music_stop();
			*screen_type = st->state_object_next_screen;
			return;
		}
		else
		{
			*screen_type = st->state_object_curr_screen;
		}

		// Draw sprites first.
		hide_actor();
		//engine_enemy_manager_hide();
		//engine_gamer_manager_hide();
		return;
	}

	delay = engine_delay_manager_update();
	if( delay )
	{
		engine_delay_manager_load( PASS_SCREEN_DELAY2 );
		engine_memo_manager_pass( perfect );

		// Only award 2000pts on normal levels i.e. not boss!
		if( fight_type_enemy == st->state_object_fight_type )
		{
			if( perfect )
			{
				engine_score_manager_finish_bonus();
			}
		}

		//if( !st->state_object_mydebugger )
		//{
			engine_audio_manager_music_play_norepeat( mus_type_level );
		//}

		event_stage = event_stage_pause;
	}

	// Draw sprites first.
	if( event_stage_start == event_stage )
	{
		draw_actor();
		//engine_enemy_manager_draw();
		//engine_gamer_manager_draw();
	}
	else
	{
		hide_actor();
		//engine_enemy_manager_hide();
		//engine_gamer_manager_hide();
	}

	*screen_type = st->state_object_curr_screen;
}

static void draw_actor()
{
	struct_state_object *st = &global_state_object;
	if( fight_type_enemy == st->state_object_fight_type )
	{
		engine_enemy_manager_draw();
	}
	else
	{
		engine_boss_manager_draw();
	}

	engine_gamer_manager_draw();
}
static void hide_actor()
{
	struct_state_object *st = &global_state_object;
	if( fight_type_enemy == st->state_object_fight_type )
	{
		engine_enemy_manager_hide();
	}
	else
	{
		engine_boss_manager_hide();
	}

	engine_gamer_manager_hide();
}

static void next_level()
{
	struct_state_object *st = &global_state_object;

	// Boss levels.
	unsigned char boss1, boss2;
	if( fight_type_enemy == st->state_object_fight_type )
	{
		boss1 = ( 0 == ( st->state_object_round_data + 1 ) % ( MAX_ROUNDS ) );
		boss2 = ( 0 == ( st->state_object_round_data + 1 ) % ( MAX_ROUNDS / 2 ) );
		if( boss1 || boss2 )
		{
			// TODO uncomment this line to integrate boss fights.
			st->state_object_next_screen = screen_type_prep;
			return;
		}
	}

	// Clocked game!
	if( MAX_WORLDS - 1 == st->state_object_world_data  && MAX_ROUNDS - 1 == st->state_object_round_data )
	{
		st->state_object_next_screen = screen_type_beat;
		return;
	}

	// TODO  here is where we check to go to boss level if there are any!!
	st->state_object_round_data++;
	if( st->state_object_round_data >= MAX_ROUNDS )
	{
		st->state_object_round_data = 0;
		st->state_object_world_data++;
	}
}