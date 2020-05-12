#include "ready_screen.h"
//#include "..\engine\audio_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
//#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
//#include "..\engine\level_manager.h"
//#include "..\engine\state_manager.h"
//#include "..\engine\timer_manager.h"
//#include "..\devkit\_sms_manager.h"

//#define READY_SCREEN_DELAY	0

void screen_ready_screen_load()
{
	//struct_state_object *st = &global_state_object;
	//st->state_object_curr_screen = screen_type_ready;
	//st->state_object_next_screen = screen_type_play;

	//engine_delay_manager_load( READY_SCREEN_DELAY );

	engine_enemy_manager_reset_home();
	engine_gamer_manager_reset();
}

void screen_ready_screen_update( unsigned char *screen_type )
{
	//struct_state_object *st = &global_state_object;
	//unsigned char delay;

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	//delay = engine_delay_manager_update();
	//if( delay )
	//{
	//	*screen_type = st->state_object_next_screen;
	//	return;
	//}

	//*screen_type = st->state_object_curr_screen;
	*screen_type = screen_type_play;
}