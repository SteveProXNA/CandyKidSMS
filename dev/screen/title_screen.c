#include "title_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\global_manager.h"
#include "..\engine\hack_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\option_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\timer_manager.h"
#include "..\object\locale_object.h"
#include "..\devkit\_sms_manager.h"
#include <stdlib.h>

#define TITLE_FLASH_DELAY	50
#define LOCAL_CHEAT_TOTAL	5
#define COIN_TEXT_X			6

static unsigned char event_stage;
static unsigned char flash_count;
static unsigned char cheat_count;
static unsigned char distance;

void screen_title_screen_load()
{
	struct_state_object *st = &global_state_object;
	struct_hack_object *ho = &global_hack_object;
	distance = menu_type_double;

	// Clear menu area first.
	engine_option_manager_clear();

	engine_locale_manager_draw_text( 1, SCREEN_TILE_LEFT + COIN_TEXT_X + 2, TEXT4_Y );
	engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + 2, BOTT_TEXT_Y );

	st->state_object_localcheat = 0;
	if( ho->hack_object_invincibie )
	{
		engine_locale_manager_draw_text( 2, SCREEN_TILE_LEFT + 2, BOTT_TEXT_Y );
		st->state_object_localcheat = 1;
	}

	engine_delay_manager_load( TITLE_FLASH_DELAY );
	event_stage = event_stage_start;
	flash_count = 0;
	cheat_count = 0;

	distance = menu_type_double;
	engine_option_manager_draw_bonus( distance );
	engine_option_manager_draw_candy( distance );

	st->state_object_next_screen = screen_type_start;

	//st->state_object_curr_screen = screen_type_init;
	//st->state_object_curr_screen = screen_type_start;
	st->state_object_curr_screen = screen_type_title;
}

void screen_title_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	struct_hack_object *ho = &global_hack_object;
	unsigned char input;
	unsigned char delay;

	engine_option_manager_draw_actor( distance );
	if( !ho->hack_object_delay_test )
	{
		engine_option_manager_update( st->state_object_curr_screen );
	}

	// Set the current screen first.
	*screen_type = st->state_object_curr_screen;
	delay = engine_delay_manager_update();


	// Enable slight pause for movement.
	if( event_stage_pause == event_stage )
	{
		if( delay )
		{
			*screen_type = st->state_object_next_screen;
		}

		return;
	}


	//delay = engine_delay_manager_update();
	if( delay )
	{
		if( !ho->hack_object_delay_test )
		{
			flash_count = 1 - flash_count;
		}

		if( flash_count )
		{
			engine_option_manager_clear(); 
			//engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + 2, TEXT4_Y + 1 );
		}
		else
		{
			engine_locale_manager_draw_text( 1, SCREEN_TILE_LEFT + COIN_TEXT_X + 2, TEXT4_Y );
		}
	}

	input = engine_input_manager_hold( input_type_fire1 );
	if( input )
	{
		event_stage = event_stage_pause;
		engine_delay_manager_load( SOUND_SCREEN_DELAY );

		if( !ho->hack_object_delay_test )
		{
			engine_audio_manager_sfx_play( sfx_type_accept );
		}

		return;
	}

	if( !ho->hack_object_invincibie )
	{
		input = engine_input_manager_hold( input_type_fire2 );
		if( input )
		{
			cheat_count++;
			if( cheat_count >= LOCAL_CHEAT_TOTAL )
			{
				engine_audio_manager_sfx_play( sfx_type_power );
				engine_locale_manager_draw_text( 2, SCREEN_TILE_LEFT + 2, BOTT_TEXT_Y );
				st->state_object_localcheat = 1;
			}
		}
	}

	rand();
}