#include "init_screen.h"
#include "..\engine\asm_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\content_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\main_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\score_manager.h"
#include "..\devkit\_sms_manager.h"

void screen_init_screen_load()
{
	// TODO delete used for debugging!!
	engine_main_manager_load();


	devkit_SMS_displayOff();

	engine_asm_manager_clear_VRAM();
	engine_content_manager_load_tiles_font();
	engine_content_manager_load_tiles_game();
	engine_content_manager_load_sprites_game();

	// Draw tree border with exits.
	engine_board_manager_border( border_type_game );
	engine_board_manager_side_tile();

	// Reset all score data.
	engine_score_manager_text();
	engine_score_manager_init();
	engine_memo_manager_option();

	devkit_SMS_displayOn();
}

void screen_init_screen_update( unsigned char *screen_type )
{
	//*screen_type = screen_type_init;
	//*screen_type = screen_type_prep;
	*screen_type = screen_type_load;
}
