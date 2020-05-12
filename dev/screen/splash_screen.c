#include "splash_screen.h"
#include "..\devkit\_sms_manager.h"
#include "..\engine\audio_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\locale_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\storage_manager.h"
#include "..\engine\timer_manager.h"
#include "..\object\locale_object.h"

#define SPLASH_SCREEN_DELAY		150
#define ERASE_SCREEN_DELAY		75

void screen_splash_screen_load()
{
	engine_delay_manager_load( SPLASH_SCREEN_DELAY );
	engine_reset_manager_load( ERASE_SCREEN_DELAY );

	devkit_SMS_displayOff();
	engine_content_manager_load_tiles_font();
	engine_content_manager_load_tiles_splash();
	devkit_SMS_displayOn();
}

void screen_splash_screen_update( unsigned char *screen_type )
{
	struct_state_object *st = &global_state_object;
	unsigned char delay;
	unsigned char input1;
	unsigned char input2;
	unsigned char check;

	delay = engine_delay_manager_update();
	input1 = engine_input_manager_hold( input_type_fire1 );
	input2 = engine_input_manager_move( input_type_fire2 );
	if( input2 )
	{
		check = engine_reset_manager_update();
		if( check )
		{
			engine_storage_manager_erase();
			st->state_object_availables = 0;

			engine_reset_manager_reset();
			engine_locale_manager_draw_text( 23, 24, 23 );
		}
	}
	else
	{
		engine_reset_manager_reset();
	}


	if( delay || input1 )
	{
		*screen_type = screen_type_begin;
		return;
	}

	*screen_type = screen_type_splash;
}