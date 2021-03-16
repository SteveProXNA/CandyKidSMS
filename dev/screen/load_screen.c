#include "load_screen.h"
#include "..\engine\asm_manager.h"
#include "..\engine\actor_manager.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\timer_manager.h"
#include "..\object\locale_object.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"
#include <stdlib.h>

#define LOAD_SCREEN_DELAY	150

static void print_level();

void screen_load_screen_load()
{
	struct_state_object *st = &global_state_object;

	st->state_object_curr_screen = screen_type_load;
	st->state_object_next_screen = screen_type_ready;

	engine_delay_manager_load( LOAD_SCREEN_DELAY );

	// Reset all score data.
	engine_score_manager_load();

	// Set all actor variables.
	engine_enemy_manager_reset_home();
	engine_gamer_manager_reset();

	engine_gamer_manager_load();
	engine_enemy_manager_load();

	engine_level_manager_clear();
	engine_level_manager_load_level( st->state_object_world_data, st->state_object_round_data );
	engine_level_manager_directions();
	engine_level_manager_draw_level();

	print_level();
}

void screen_load_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char delay;
	unsigned char input;
	unsigned char index;

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	delay = engine_delay_manager_update();
	input = devkit_SMS_getKeysStatus();
	if( delay || input )
	{
		index = rand() % MAX_MUSIC;
		engine_level_manager_draw_middle();
		engine_audio_manager_music_play( index + 3 );
		*screen_type = st->state_object_next_screen;
		return;
	}

	*screen_type = st->state_object_curr_screen;
}

static void print_level()
{
	engine_board_manager_midd_text();
	engine_memo_manager_levels( 14, 11, 12 );

	devkit_SMS_mapROMBank( FIXED_BANK );
	engine_font_manager_draw_text( locale_object_texts[ 12 ], SCREEN_TILE_LEFT + 8, 11 );
	engine_font_manager_draw_text( locale_object_texts[ 13 ], SCREEN_TILE_LEFT + 8, 12 );
}