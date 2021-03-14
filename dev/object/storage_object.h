#ifndef _SAVEGAME_OBJECT_H_
#define _SAVEGAME_OBJECT_H_

// Reference: http://www.smspower.org/forums/16013-DevkitSMSSMSlibMissingRequestingFeatures#91899
typedef struct tag_struct_storage_object
{
	unsigned long Magic;
	unsigned long save_high_score;

	unsigned char save_trees_type;
	unsigned char save_exits_type;
	unsigned char save_difficulty;
	unsigned char save_game_speed;

	unsigned char save_world_data;
	unsigned char save_round_data;

	unsigned char save_image_kid;
	unsigned char save_image_pro;
	unsigned char save_image_adi;
	unsigned char save_image_suz;

	unsigned char terminal;

} struct_storage_object;

#endif//_SAVEGAME_OBJECT_H_