#include "hack_manager.h"
#include "global_manager.h"
#include "enum_manager.h"
#include "state_manager.h"

// Global variable.
struct_hack_object global_hack_object;

#define PEEK( addr)			(* ( unsigned char *)( addr ) )
#define POKE( addr, data )	(* ( unsigned char *)( addr ) = ( data ) )

#define HACKER_START		0x0050

// TODO delete this - set only during debugging / play testing
#ifdef _CONSOLE
#else
#pragma disable_warning 110
#pragma disable_warning 126
#endif

void engine_hack_manager_init()
{
	struct_hack_object *ho = &global_hack_object;

	ho->hack_object_delay_test = 0;
	ho->hack_object_mydebugger = 0;
	ho->hack_object_invincibie = 0;
	ho->hack_object_full_boost = 0;

	ho->hack_object_trees_type = 0;
	ho->hack_object_exits_type = 0;
	ho->hack_object_difficulty = 0;
	ho->hack_object_pace_speed = 0;

	ho->hack_object_world_data = 0;
	ho->hack_object_round_data = 0;
	ho->hack_object_music_data = 0;
	ho->hack_object_sound_data = 0;

	// Zero means enable enemy.
	ho->hack_object_enemy_move[ actor_type_pro ] = 0;
	ho->hack_object_enemy_move[ actor_type_adi ] = 0;
	ho->hack_object_enemy_move[ actor_type_suz ] = 0;
}

void engine_hack_manager_load()
{
	struct_hack_object *ho = &global_hack_object;

#ifndef _CONSOLE

	ho->hack_object_delay_test = PEEK( HACKER_START - 2 );			// 0x004E		// Used to speed through any game delay.
	ho->hack_object_mydebugger = PEEK( HACKER_START - 1 );			// 0x004F		// Used to show debugging info for game.
	ho->hack_object_invincibie = PEEK( HACKER_START + 0 );			// 0x0050		// Non-zero value enables invincibility.
	ho->hack_object_full_boost = PEEK( HACKER_START + 1 );			// 0x0051		// Non-zero value enables maximum boost.

	ho->hack_object_trees_type = PEEK( HACKER_START + 2 );			// 0x0052		// Set value to 1=Show otherwise 2=Kill.
	ho->hack_object_exits_type = PEEK( HACKER_START + 3 );			// 0x0053		// Set value to 1=Open otherwise 2=Shut.
	ho->hack_object_difficulty = PEEK( HACKER_START + 4 );			// 0x0054		// Set value to 1=Easy otherwise 2=Hard.
	ho->hack_object_pace_speed = PEEK( HACKER_START + 5 );			// 0x0055		// Set value to 1=Slow otherwise 2=Fast.

	ho->hack_object_world_data = PEEK( HACKER_START + 6 );			// 0x0056		// Set start World no currently 1 to 10.
	ho->hack_object_round_data = PEEK( HACKER_START + 7 );			// 0x0057		// Set start Round no currently 1 to 10.
	ho->hack_object_music_data = PEEK( HACKER_START + 8 );			// 0x0058		// Set 0=Music to play otherwise silent.
	ho->hack_object_sound_data = PEEK( HACKER_START + 9 );			// 0x0059		// Set 0=Sound to play otherwise silent.

	ho->hack_object_enemy_move[ actor_type_pro ] = PEEK( HACKER_START + 16 );
	ho->hack_object_enemy_move[ actor_type_adi ] = PEEK( HACKER_START + 17 );
	ho->hack_object_enemy_move[ actor_type_suz ] = PEEK( HACKER_START + 18 );

#endif
}

void engine_hack_manager_invert()
{
	struct_hack_object *ho = &global_hack_object;
	struct_state_object *st = &global_state_object;

	// Ensure all commented out : used for testing!
	//ho->hack_object_delay_test = 0;
	//ho->hack_object_mydebugger = 0;
	//ho->hack_object_invincibie = 1;
	//ho->hack_object_full_boost = 1;

	// These need offset of one to differentiate from SRAM values.
	//ho->hack_object_trees_type = 1 + 1;
	//ho->hack_object_exits_type = 0 + 1;
	//ho->hack_object_difficulty = 1 + 1;
	//ho->hack_object_pace_speed = 0 + 1;


	// Enable enemy movement via ROM hack = 0.
	//ho->hack_object_enemy_move[ actor_type_pro ] = 0;
	//ho->hack_object_enemy_move[ actor_type_adi ] = 0;
	//ho->hack_object_enemy_move[ actor_type_suz ] = 0;

	// Disable  enemy movement via ROM hack = 1.
	//ho->hack_object_enemy_move[ actor_type_pro ] = 1;
	//ho->hack_object_enemy_move[ actor_type_adi ] = 1;
	//ho->hack_object_enemy_move[ actor_type_suz ] = 1;



	// Trees.
	if( ho->hack_object_trees_type )
	{
		st->state_object_trees_type = ( tree_type_death + 1 ) == ho->hack_object_trees_type ? tree_type_death : tree_type_avoid;
	}

	// Exits.
	if( ho->hack_object_exits_type )
	{
		st->state_object_exits_type = ( exit_type_closed + 1 ) == ho->hack_object_exits_type ? exit_type_closed : exit_type_public;
	}

	// Difficulty.
	if( ho->hack_object_difficulty )
	{
		st->state_object_difficulty = ( diff_type_hard + 1 ) == ho->hack_object_difficulty ? diff_type_hard : diff_type_easy;
	}

	// Game speed.
	if( ho->hack_object_pace_speed )
	{
		st->state_object_pace_speed = ( pace_type_fast + 1 ) == ho->hack_object_pace_speed ? pace_type_fast : pace_type_slow;
	}


	// World.
	if( ho->hack_object_world_data )
	{
		if( ho->hack_object_world_data > MAX_WORLDS )
		{
			ho->hack_object_world_data = MAX_WORLDS;
		}

		// Zero-based index.
		st->state_object_world_data = ho->hack_object_world_data - 1;
	}

	// Round.
	if( ho->hack_object_round_data )
	{
		if( ho->hack_object_round_data > MAX_ROUNDS )
		{
			ho->hack_object_round_data = MAX_ROUNDS;
		}

		// Zero-based index.
		st->state_object_round_data = ho->hack_object_round_data - 1;
	}


	// Invert default values.
	ho->hack_object_music_data = !ho->hack_object_music_data;
	ho->hack_object_sound_data = !ho->hack_object_sound_data;
}