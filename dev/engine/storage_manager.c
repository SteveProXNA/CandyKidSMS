#include "storage_manager.h"
#include "enemy_manager.h"
#include "enum_manager.h"
#include "gamer_manager.h"
#include "global_manager.h"
#include "state_manager.h"
#include "..\devkit\_sms_manager.h"

#define MAGIC			0xACE0B004
#define FINAL			0xFE

// Global variable.
struct_storage_object global_savegame_object;


// Reference:
// https://www.smspower.org/forums/16013-DevkitSMSSMSlibMissingRequestingFeatures
unsigned char engine_storage_manager_available()
{
	struct_storage_object *savegame = ( struct_storage_object* ) ( devkit_SMS_SRAM() );
	unsigned char foundMagic;

	devkit_SMS_enableSRAM();
	foundMagic = MAGIC == savegame->Magic;
	devkit_SMS_disableSRAM();
	return foundMagic;

	//return 0;
}

void engine_storage_manager_read()
{
	struct_storage_object *savegame = ( struct_storage_object* ) ( devkit_SMS_SRAM() );
	struct_state_object *st = &global_state_object;

	devkit_SMS_enableSRAM();

	//// adriana
	st->state_object_high_score = savegame->save_high_score;

	st->state_object_difficulty = savegame->save_difficulty;
	st->state_object_pace_speed = savegame->save_game_speed;
	st->state_object_trees_type = savegame->save_trees_type;
	st->state_object_exits_type = savegame->save_exits_type;

	st->state_object_world_data = savegame->save_world_data;
	st->state_object_round_data = savegame->save_round_data;

	engine_gamer_manager_images( savegame->save_image_kid );
	engine_enemy_manager_images( savegame->save_image_pro, savegame->save_image_adi, savegame->save_image_suz );

	devkit_SMS_disableSRAM();
}

void engine_storage_manager_write()
{
	struct_storage_object *savegame = ( struct_storage_object* ) ( devkit_SMS_SRAM() );

	struct_state_object *st = &global_state_object;
	struct_gamer_object *go = &global_gamer_object;
	struct_enemy_object *eo;


	// TODO delete
	//st->state_object_high_score += 20;
	////st->state_object_trees_type = 1 - st->state_object_trees_type;
	//st->state_object_exits_type = 1 - st->state_object_exits_type;
	//st->state_object_round_data += 1;
	//if( 10 == st->state_object_round_data )
	//{
	//	st->state_object_round_data = 0;
	//}

	//go->image = 1 - go->image;
	//eo = &global_enemy_objects[ actor_type_pro ]; eo->image = 1 - eo->image;
	//eo = &global_enemy_objects[ actor_type_adi ]; eo->image = 1 - eo->image;
	//eo = &global_enemy_objects[ actor_type_suz ]; eo->image = 1 - eo->image;
	// TODO delete


	devkit_SMS_enableSRAM();
	savegame->Magic = MAGIC;
	savegame->save_high_score = st->state_object_high_score;

	savegame->save_difficulty = st->state_object_difficulty;
	savegame->save_game_speed = st->state_object_pace_speed;
	savegame->save_trees_type = st->state_object_trees_type;
	savegame->save_exits_type = st->state_object_exits_type;

	savegame->save_world_data = st->state_object_world_data;
	savegame->save_round_data = st->state_object_round_data;

	savegame->save_image_kid = go->image;
	eo = &global_enemy_objects[ actor_type_pro ]; savegame->save_image_pro = eo->image;
	eo = &global_enemy_objects[ actor_type_adi ]; savegame->save_image_adi = eo->image;
	eo = &global_enemy_objects[ actor_type_suz ]; savegame->save_image_suz = eo->image;

	savegame->terminal = FINAL;
	devkit_SMS_disableSRAM();
}

void engine_storage_manager_erase()
{
	struct_storage_object *savegame = ( struct_storage_object* ) ( devkit_SMS_SRAM() );

	devkit_SMS_enableSRAM();
	savegame->Magic = 0x00000000;
	savegame->save_high_score = DEF_HI_SCORE;

	savegame->save_trees_type = tree_type_avoid;
	savegame->save_exits_type = exit_type_public;
	savegame->save_difficulty = diff_type_easy;
	savegame->save_game_speed = pace_type_slow;

	savegame->save_world_data = 0;
	savegame->save_round_data = 0;

	savegame->save_image_kid = 0;
	savegame->save_image_pro = 0;
	savegame->save_image_adi = 0;
	savegame->save_image_suz = 0;

	savegame->terminal = FINAL;
	devkit_SMS_disableSRAM();
}