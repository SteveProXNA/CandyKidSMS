#ifndef _HACK_OBJECT_H_
#define _HACK_OBJECT_H_

#include "..\engine\global_manager.h"

typedef struct tag_struct_hack_object
{
	unsigned char hack_object_delay_test;
	unsigned char hack_object_mydebugger;
	unsigned char hack_object_invincibie;
	unsigned char hack_object_full_boost;

	unsigned char hack_object_trees_type;
	unsigned char hack_object_exits_type;
	unsigned char hack_object_difficulty;
	unsigned char hack_object_pace_speed;

	unsigned char hack_object_world_data;
	unsigned char hack_object_round_data;
	unsigned char hack_object_music_data;
	unsigned char hack_object_sound_data;

	unsigned char hack_object_enemy_move[ MAX_ENEMIES ];

} struct_hack_object;

#endif//_HACK_OBJECT_H_