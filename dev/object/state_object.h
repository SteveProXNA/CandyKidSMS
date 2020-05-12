#ifndef _STATE_OBJECT_H_
#define _STATE_OBJECT_H_

typedef struct tag_struct_state_object
{
	unsigned char state_object_availables;
	unsigned char state_object_localcheat;
	unsigned int  state_object_high_score;

	unsigned char state_object_trees_type;
	unsigned char state_object_exits_type;
	unsigned char state_object_difficulty;
	unsigned char state_object_pace_speed;

	unsigned char state_object_world_data;
	unsigned char state_object_round_data;
	unsigned char state_object_actor_kill;
	unsigned char state_object_fight_type;

	unsigned char state_object_curr_screen;
	unsigned char state_object_next_screen;

} struct_state_object;

#endif//_STATE_OBJECT_H_