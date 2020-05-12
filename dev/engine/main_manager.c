#include "main_manager.h"
#include "content_manager.h"
#include "enemy_manager.h"
#include "enum_manager.h"
#include "gamer_manager.h"
#include "global_manager.h"
#include "hack_manager.h"
#include "state_manager.h"
#include "storage_manager.h"

void engine_main_manager_init()
{
	engine_state_manager_init();

	engine_gamer_manager_init();
	engine_enemy_manager_init();
}

void engine_main_manager_load()
{
	struct_state_object *st = &global_state_object;
	unsigned char storage;

	// Set default global state.
	engine_hack_manager_init();
	engine_hack_manager_load();			// TODO read from SRAM before ROM hack

	// adriana
	st->state_object_high_score = DEF_HI_SCORE;
	st->state_object_actor_kill = actor_type_kid;

	// Check if global state previously stored.
	storage = engine_storage_manager_available();
	if( storage )
	{
		engine_storage_manager_read();
		st->state_object_availables = 1;
	}

	// Invert any hack overrides...
	//engine_hack_manager_load();		// Uncomment out will overwerite SRAM values
	engine_hack_manager_invert();		// TODO DELETE any hardcoded stuff
}

//void engine_main_manager_debug()
//{
//	struct_state_object *st = &global_state_object;
//	if( !st->state_object_load_asset )
//	{
//		return;
//	}
//
//	engine_content_manager_load_tiles_font();
//	engine_content_manager_load_tiles_game();
//	engine_content_manager_load_sprites_game();
//}

void engine_main_manager_save()
{
	engine_storage_manager_write();
}