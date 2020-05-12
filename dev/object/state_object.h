#ifndef _STATE_OBJECT_H_
#define _STATE_OBJECT_H_

typedef struct tag_struct_state_object
{
	unsigned char state_object_availables;
	unsigned char state_object_mydebugger;
	unsigned char state_object_full_boost;
	unsigned char state_object_invincibie;
	unsigned char state_object_localcheat;
	unsigned int  state_object_high_score;

	unsigned char state_object_difficulty;
	unsigned char state_object_pace_speed;
	unsigned char state_object_trees_type;
	unsigned char state_object_exits_type;

	unsigned char state_object_world_data;
	unsigned char state_object_round_data;
	//unsigned char state_object_music_data;
	//unsigned char state_object_sound_data;

	unsigned char state_object_actor_kill;
	unsigned char state_object_delay_test;
	//unsigned char state_object_load_asset;

	unsigned char state_object_curr_screen;
	unsigned char state_object_next_screen;

	unsigned char state_object_enemy_move[];

} struct_state_object;

#endif//_STATE_OBJECT_H_