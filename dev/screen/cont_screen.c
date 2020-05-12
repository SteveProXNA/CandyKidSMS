#include "cont_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\boss_manager.h"
#include "..\engine\collision_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"

#define CONT_SCREEN_DELAY	10
#define CONT_X				10
#define TEXT_Y				11
#define OPT1_X				CONT_X + 0
#define OPT2_X				CONT_X + 5

static unsigned char event_stage;

static void display_cursor();
static unsigned char cursorX[ 2 ] = { OPT1_X, OPT2_X };
static unsigned char cursor;

void screen_cont_screen_load()
{
	engine_audio_manager_music_stop();
	engine_delay_manager_load( CONT_SCREEN_DELAY );
	engine_memo_manager_draw( 17, 18 );
	cursor = 0;

	display_cursor();
	event_stage = event_stage_start;
}

void screen_cont_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char input[ 3 ] = { 0, 0, 0 };
	unsigned char delay;

	if( event_stage_pause == event_stage )
	{
		// Draw sprites first.
		if( fight_type_enemy == st->state_object_fight_type )
		{
			engine_enemy_manager_hide();
		}
		else
		{
			engine_boss_manager_hide();
		}

		engine_gamer_manager_hide_death();

		delay = engine_delay_manager_update();
		if( delay )
		{
			if( 0 == cursor )
			{
				engine_collision_manager_reset_death();

				// Reset enemy that killed Kid to scatter mode only.
				// Nasty bug : do NOT set when death tree kills Kid!
				if( fight_type_enemy == st->state_object_fight_type )
				{
					if( actor_type_pro == st->state_object_actor_kill || actor_type_adi == st->state_object_actor_kill || actor_type_suz == st->state_object_actor_kill )
					{
						engine_enemy_manager_reset_mode( st->state_object_actor_kill, enemymove_type_tour );
					}
				}
				else
				{
					//if( actor_type_boss1 == st->state_object_actor_kill || actor_type_boss2 == st->state_object_actor_kill )
					//{
					// TODO stevepro Adriana add this method to reset boss(es) to tour mode irrespective!
					//engine_boss_manager_reset_mode( st->state_object_actor_kill, enemymove_type_tour );
					//}
				}

				// If Kid dies from death tree then update directions
				// because Mamas can now move through this empty tile.
				if( actor_type_tree == st->state_object_actor_kill && tree_type_death == st->state_object_trees_type )
				{
					engine_level_manager_directions();
				}

				engine_score_manager_reset_boost();
				engine_score_manager_reset_lives();
				engine_level_manager_draw_middle();
				engine_audio_manager_music_resume();

				*screen_type = fight_type_enemy == st->state_object_fight_type ? screen_type_ready : screen_type_fight;
				return;
			}
			else
			{
				*screen_type = screen_type_over;
				return;
			}
		}
		else
		{
			*screen_type = screen_type_cont;
			return;
		}
	}

	// Draw sprites last.
	if( fight_type_enemy == st->state_object_fight_type )
	{
		engine_enemy_manager_hide();
	}
	else
	{
		engine_boss_manager_hide();
	}

	engine_gamer_manager_hide_death();

	input[ 0 ] = engine_input_manager_hold( input_type_left );
	input[ 1 ] = engine_input_manager_hold( input_type_right );
	if( input[ 0 ] || input[ 1 ] )
	{
		cursor = 1 - cursor;
		display_cursor();
	}

	input[ 2 ] = engine_input_manager_hold( input_type_fire1 );
	if( input[ 2 ] )
	{
		// TODO play sound FX
		//engine_audio_manager_sound_accept();		// adriana
		event_stage = event_stage_pause;
		return;
	}

	*screen_type = screen_type_cont;
}

static void display_cursor()
{
	engine_font_manager_draw_text( LOCALE_SELECT_SPACE, OPT1_X, TEXT_Y + 1 );
	engine_font_manager_draw_text( LOCALE_SELECT_SPACE, OPT2_X, TEXT_Y + 1 );
	engine_font_manager_draw_text( LOCALE_SELECT_ARROW, cursorX[ cursor ], TEXT_Y + 1 );
}