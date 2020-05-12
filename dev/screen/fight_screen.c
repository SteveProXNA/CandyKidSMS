#include "fight_screen.h"
#include "..\engine\boss_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
//#include "..\engine\state_manager.h"
//#include "..\devkit\_sms_manager.h"

void screen_fight_screen_load()
{
	// TODO
	//engine_boss_manager_reset_home();
	//engine_enemy_manager_reset_home();
	engine_gamer_manager_reset();

	//engine_font_manager_draw_text( "FIGHT SCREEN!!", 4, 10 );
}

void screen_fight_screen_update( unsigned char *screen_type )
{
	// Draw sprites first.
	engine_boss_manager_draw();
	engine_gamer_manager_draw();

	//*screen_type = screen_type_fight;
	*screen_type = screen_type_boss;
}
