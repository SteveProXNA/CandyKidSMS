#include "dead_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\collision_manager.h"
//#include "..\engine\command_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\tile_manager.h"
#include "..\engine\timer_manager.h"
#include <stdlib.h>

#define DEATH_SCREEN_DELAY		100
#define FLASH_SCREEN_DELAY		20
//#define RESET_SCREEN_DELAY		75

//#define DEATH_SCREEN_DELAY		15
//#define FLASH_SCREEN_DELAY		5

static unsigned char death_frame;
static unsigned char event_stage;
static unsigned char flash_count;

static void reset_death();
static unsigned char screen;

void screen_dead_screen_load()
{
	struct_state_object *st = &global_state_object;
	unsigned char lives;
	unsigned char index;
	engine_audio_manager_music_stop();

//	engine_command_manager_load();
	engine_frame_manager_load();

	//engine_frame_manager_draw();
	//engine_delay_manager_draw();

	// TODO play death sound FX
	engine_delay_manager_load( DEATH_SCREEN_DELAY );
	//engine_reset_manager_load( RESET_SCREEN_DELAY );

	event_stage = event_stage_start;
	death_frame = 0;
	flash_count = 0;

	engine_score_manager_update_lives( -1 );
	lives = engine_score_manager_get_value( score_type_lives );
	screen = ( 0 == lives ) ? screen_type_cont : screen_type_ready;
	//screen = screen_type_cont;
	//screen = screen_type_ready;

	//if( !st->state_object_mydebugger )
	//{
		//engine_audio_manager_sfx_play( sfx_type_accept );
	index = rand() % MAX_MUSIC;
	engine_audio_manager_sfx_play( index + 3 );
	//}
}

void screen_dead_screen_update( unsigned char *screen_type )
{
	struct_frame_object *fo = &global_frame_object;
	struct_state_object *st = &global_state_object;
	struct_enemy_object *eo;

	unsigned char enemy_direction = direction_type_none;
	unsigned char input;
	unsigned char enemy;
	unsigned char delay;
	unsigned int frame = fo->frame_count;

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw_death( death_frame );


	// Check if Kid want to advance.
	//if( st->state_object_mydebugger )
	//{
		input = engine_input_manager_hold( input_type_fire2 );
		if( input )
		{
			if( screen_type_ready == screen )
			{
				engine_audio_manager_music_resume();
				reset_death();
			}

			*screen_type = screen;
			return;
		}
	//}

	//engine_frame_manager_draw();
	//engine_delay_manager_draw();

	engine_frame_manager_update();
	if( event_stage_pause == event_stage )
	{
		delay = engine_delay_manager_update();
		if( delay )
		{
			flash_count++;
			if( screen_type_ready == screen )
			{
				death_frame = 1 - death_frame;
			}

			if( flash_count >= 7 )
			{
				if( screen_type_ready == screen )
				{
					engine_audio_manager_music_resume();
					reset_death();
				}

				*screen_type = screen;
				return;
			}
		}
	}


	// Move enemies.
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];

		// Swap hands first if enemy moving and not dead.
		if( eo->mover && lifecycle_type_dead != eo->lifecycle )
		{
			engine_enemy_manager_dohand( enemy );
		}

		// If enemy not moving then skip all movement code.
		if( !eo->mover )
		{
			continue;
		}

		// Move enemy.
		if( direction_type_none != eo->direction && lifecycle_type_move == eo->lifecycle )
		{
			//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
			engine_enemy_manager_update( enemy );
		}
		if( direction_type_none != eo->direction && lifecycle_type_idle == eo->lifecycle )
		{
			engine_enemy_manager_stop( enemy );
		}
		// For continuity we want to check if actor can move immediately after stopping.
		if( direction_type_none == eo->direction && lifecycle_type_idle == eo->lifecycle )
		{
			enemy_direction = engine_enemy_manager_gohome_direction( enemy );
			if( direction_type_none != enemy_direction )
			{
//				engine_command_manager_add( frame, command_type_enemy_mover, ( enemy | ( enemy_direction << 4 ) ) );
				engine_enemy_manager_move( enemy, enemy_direction );
			}
		}
	}

	// Execute all commands for this frame.
//	engine_command_manager_execute( frame );


	if( event_stage_start == event_stage )
	{
		delay = engine_delay_manager_update();
		if( delay )
		{
			engine_delay_manager_load( FLASH_SCREEN_DELAY );
			event_stage = event_stage_pause;
		}
	}

	*screen_type = screen_type_dead;
}

static void reset_death()
{
	struct_state_object *st = &global_state_object;
	unsigned char boost;

	// Kid collided with death tree on border so redraw.
	engine_collision_manager_reset_death();

	// Reset enemy that killed Kid to scatter mode only.
	// Nasty bug : do NOT set when death tree kills Kid!
	if( actor_type_pro == st->state_object_actor_kill || actor_type_adi == st->state_object_actor_kill || actor_type_suz == st->state_object_actor_kill )
	{
		engine_enemy_manager_reset_mode( st->state_object_actor_kill, enemymove_type_tour );
	}

	// IMPORTANT I've decided NOT to reset boost on loss of life.
	// only reset boost if zero or pass level or continue game.
	boost = engine_score_manager_get_value( score_type_boost );
	if( 0 == boost )
	{
		engine_score_manager_reset_boost();
	}
}
