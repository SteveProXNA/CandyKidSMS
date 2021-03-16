#include "prep_screen.h"
#include "..\engine\asm_manager.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\boss_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\collision_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\hack_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\timer_manager.h"
#include "..\object\locale_object.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"
#include <stdlib.h>

#define PREP_SCREEN_DELAY	150

static void setup_level( unsigned char tile_type );
static void print_level();

void screen_prep_screen_load()
{
	struct_state_object *st = &global_state_object;
	struct_level_object *lo = &global_level_object;
	struct_hack_object *ho = &global_hack_object;
	unsigned char oneup_count;

	st->state_object_curr_screen = screen_type_prep;
	st->state_object_next_screen = screen_type_fight;

	engine_delay_manager_load( PREP_SCREEN_DELAY );

	// Load screen
	// Reset all score data.
	engine_score_manager_load();

	engine_gamer_manager_reset();

	// Force override enemy move!
	engine_gamer_manager_load();
	engine_boss_manager_setup( st->state_object_round_data );
	engine_boss_manager_content();
	engine_boss_manager_load();
	engine_collision_manager_load();

	// Algorithm to determine oneup count.
	oneup_count = ( 10 + st->state_object_world_data ) * st->state_object_fight_type + ( st->state_object_difficulty * 5 );
	if( oneup_count > 45 )
	{
		oneup_count = 45;
	}

	// load oneup
	engine_level_manager_clear();
	setup_level( tile_type_trees );
	engine_level_manager_load_extra( oneup_count, tile_type_oneup );
	setup_level( tile_type_blank );
	engine_level_manager_directions();

	engine_level_manager_draw_level();
	if( !ho->hack_object_delay_test )
	{
		print_level();
	}
}

void screen_prep_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char delay;
	unsigned char input;
	unsigned char index;

	unsigned char gamer_collision = coll_type_empty;

	// Draw sprites first.
	engine_boss_manager_draw();
	engine_gamer_manager_draw();

	delay = engine_delay_manager_update();
	input = devkit_SMS_getKeysStatus();
	if( delay || input )
	{
		//index = rand() % MAX_MUSIC;
		index = engine_boss_manager_index() / MAX_ENEMIES;
		engine_level_manager_draw_middle();
		engine_audio_manager_music_play( index + 8 );
		*screen_type = st->state_object_next_screen;
		return;
	}

	*screen_type = st->state_object_curr_screen;
}

static void setup_level( unsigned char tile_type )
{
	struct_gamer_object *go = &global_gamer_object;
	struct_boss_object *bo;
	unsigned char bossX;

	// Offset one to the left for easier left to right in function.
	engine_level_manager_temp_level( go->tileX - 1, go->tileY, tile_type );
	for( bossX = 0; bossX < MAX_BOSSES; bossX++ )
	{
		bo = &global_boss_objects[ bossX ];
		if( bo->drawr )
		{
			engine_level_manager_temp_level( bo->tileX - 1, bo->tileY, tile_type );
		}
	}
}

static void print_level()
{
	struct_state_object *st = &global_state_object;
	unsigned char index = 49 + st->state_object_fight_type;

	engine_board_manager_midd_text();
	engine_memo_manager_levels( 14, 11, 12 );

	devkit_SMS_mapROMBank( FIXED_BANK );
	engine_font_manager_draw_text( locale_object_texts[ 12 ], SCREEN_TILE_LEFT + 8, 11 );
	engine_font_manager_draw_text( locale_object_texts[ index ], SCREEN_TILE_LEFT + 8, 12 );
}