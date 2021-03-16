#include "over_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\main_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\timer_manager.h"
#include "..\object\audio_object.h"

#define OVER_SCREEN_DELAY		275

void screen_over_screen_load()
{
	unsigned char x = SCREEN_TILE_LEFT + LFT_SIDE_X + 8;
	unsigned char y = TOP_SIDE_Y + 10;

	engine_audio_manager_music_stop();
	engine_delay_manager_load( OVER_SCREEN_DELAY );

	engine_locale_manager_draw_text( 19, x, y + 1 );
	engine_locale_manager_draw_text( 20, x, y + 2 );

	// Save game state to SRAM when game over.
	engine_main_manager_save();

	engine_audio_manager_music_play_norepeat( mus_type_over );
}

void screen_over_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char input;
	unsigned char delay;

	input = engine_input_manager_hold( input_type_fire1 );
	delay = engine_delay_manager_update();
	if( delay || input )
	{
		engine_audio_manager_music_stop();
		*screen_type = screen_type_begin;
		return;
	}

	// Draw sprites last.
	if( fight_type_enemy == st->state_object_fight_type )
	{
		engine_enemy_manager_hide();
	}

	engine_gamer_manager_hide_death();

	*screen_type = screen_type_over;
}
