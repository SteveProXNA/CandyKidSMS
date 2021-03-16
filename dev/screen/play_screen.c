#include "play_screen.h"
#include "..\engine\audio_manager.h"
#include "..\engine\board_manager.h"
#include "..\engine\collision_manager.h"
//#include "..\engine\command_manager.h"
#include "..\engine\enum_manager.h"
#include "..\engine\enemy_manager.h"
#include "..\engine\font_manager.h"
#include "..\engine\gamer_manager.h"
#include "..\engine\hack_manager.h"
#include "..\engine\input_manager.h"
#include "..\engine\level_manager.h"
#include "..\engine\memo_manager.h"
#include "..\engine\score_manager.h"
#include "..\engine\state_manager.h"
#include "..\engine\timer_manager.h"
#include "..\devkit\_sms_manager.h"

// IMPORTANT disable compiler warning 110
#ifdef _CONSOLE
#else
#pragma disable_warning 110
#endif

static unsigned char nextr_direction;

void screen_play_screen_load()
{
	struct_hack_object *ho = &global_hack_object;
	struct_state_object *st = &global_state_object;

	struct_enemy_object *eo;
	engine_delay_manager_load( 0 );

//	engine_command_manager_load();
	engine_frame_manager_load();

	if( ho->hack_object_mydebugger )
	{
		eo = &global_enemy_objects[ actor_type_pro ];	engine_memo_manager_debugging( actor_type_pro, eo->action );
		eo = &global_enemy_objects[ actor_type_adi ];	engine_memo_manager_debugging( actor_type_adi, eo->action );
		eo = &global_enemy_objects[ actor_type_suz ];	engine_memo_manager_debugging( actor_type_suz, eo->action );
	}

	nextr_direction = direction_type_none;
	engine_reset_manager_load( QUIT_SCREEN_DELAY );
}

void screen_play_screen_update( unsigned char *screen_type )
{
	struct_frame_object *fo = &global_frame_object;
	struct_gamer_object *go = &global_gamer_object;
	struct_state_object *st = &global_state_object;
	struct_level_object *lo = &global_level_object;
	struct_enemy_object *eo;
	unsigned char gamer_boost = 0;
	unsigned char enemy_boost = 0;
	unsigned char gamer_direction = direction_type_none;
	unsigned char enemy_direction = direction_type_none;
	unsigned char input_direction = direction_type_none;
	unsigned char gamer_collision = coll_type_empty;
	unsigned char gamer_tile_type = tile_type_blank;
	unsigned char candy_count = 0;

	unsigned char input;
	unsigned char enemy;
	unsigned char check;
	unsigned int frame = fo->frame_count;
	st->state_object_actor_kill = actor_type_kid;

	// Draw sprites first.
	engine_enemy_manager_draw();
	engine_gamer_manager_draw();

	// Continue...
	frame = fo->frame_count;
	engine_frame_manager_update();

	// Does player want to quit out?
	input = engine_input_manager_move( input_type_fire2 );
	if( input )
	{
		check = engine_reset_manager_update();
		if( check )
		{
			engine_board_manager_midd_text();
			*screen_type = screen_type_over;
			return;
		}
	}
	else
	{
		engine_reset_manager_reset();
	}


	// Move gamer.
	if( direction_type_none != go->direction && lifecycle_type_move == go->lifecycle )
	{
		//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
		input_direction = engine_input_manager_direction();
		if( direction_type_none != input_direction && gamer_direction != input_direction )
		{
			nextr_direction = gamer_direction;
		}

		engine_gamer_manager_update();

		// Check boost for next cycle.
		gamer_boost = engine_gamer_manager_input_boost( go->direction );
		if( pace_type_none != gamer_boost )
		{
//			engine_command_manager_add( frame, command_type_gamer_speed, gamer_boost );
			engine_gamer_manager_pace( gamer_boost );
		}
	}
	if( direction_type_none != go->direction && lifecycle_type_idle == go->lifecycle )
	{
		// Check gamer collision.
		gamer_tile_type = engine_level_manager_get_tile_type( go->tileX, go->tileY, go->direction, offset_type_none );
		if( tile_type_blank != gamer_tile_type )
		{
			// Collide with [death] tree, candy, bonus or one up therefore process tile accordingly...
			gamer_collision = engine_collision_manager_tile_collision( gamer_tile_type );
			if( coll_type_block == gamer_collision )
			{
				engine_gamer_manager_dead();
				st->state_object_actor_kill = actor_type_tree;
			}
		}

		engine_gamer_manager_stop();
	}
	// For continuity we want to check if actor can move immediately after stopping.
	if( direction_type_none == go->direction && lifecycle_type_idle == go->lifecycle )
	{
		if( coll_type_empty == gamer_collision )
		{
			if( direction_type_none != nextr_direction )
			{
				gamer_direction = nextr_direction;
				nextr_direction = direction_type_none;
			}
			else
			{
				gamer_direction = engine_input_manager_direction();
			}

			gamer_direction = engine_gamer_manager_find_direction( gamer_direction );
			if( direction_type_none != gamer_direction )
			{
				//engine_command_manager_add( frame, command_type_gamer_mover, gamer_direction );
				engine_gamer_manager_move( gamer_direction );

				gamer_boost = engine_gamer_manager_input_boost( gamer_direction );
				if( pace_type_none != gamer_boost )
				{
//					engine_command_manager_add( frame, command_type_gamer_speed, gamer_boost );
					engine_gamer_manager_pace( gamer_boost );
				}
			}
		}
	}


	// Move enemies.
	//for( enemy = 0; enemy < 1; enemy++ )
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];

		// Swap hands first if enemy moving and not dead.
		if( eo->mover && lifecycle_type_dead != eo->lifecycle )
		{
			engine_enemy_manager_dohand( enemy );
		}

		// If enemy not moving then skip all movement code.
		if( !eo->mover )
		{
			continue;
		}

		// Move enemy.
		if( direction_type_none != eo->direction && lifecycle_type_move == eo->lifecycle )
		{
			//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
			engine_enemy_manager_update( enemy );
		}
		if( direction_type_none != eo->direction && lifecycle_type_idle == eo->lifecycle )
		{
			engine_enemy_manager_stop( enemy );
		}
		// For continuity we want to check if actor can move immediately after stopping.
		if( direction_type_none == eo->direction && lifecycle_type_idle == eo->lifecycle )
		{
			if( enemymove_type_wait == eo->action )
			{
				if( frame >= eo->waiter )
				{
					engine_enemy_manager_reset_mode( enemy, enemymove_type_tour );
				}
			}

			if( enemymove_type_tour == eo->action || enemymove_type_kill == eo->action )
			{
				enemy_boost = engine_enemy_manager_input_boost( enemy );
				if( pace_type_none != enemy_boost )
				{
//					engine_command_manager_add( frame, command_type_enemy_speed, ( enemy | ( enemy_boost << 4 ) ) );
					engine_enemy_manager_pace( enemy, enemy_boost );
				}

				if( enemymove_type_tour == eo->action )
				{
					enemy_direction = engine_enemy_manager_scatter_direction( enemy );
				}
				else if( enemymove_type_kill == eo->action )
				{
					enemy_direction = engine_enemy_manager_attack_direction( enemy, go->tileX, go->tileY );
				}

				if( direction_type_none != enemy_direction )
				{
//					engine_command_manager_add( frame, command_type_enemy_mover, ( enemy | ( enemy_direction << 4 ) ) );
					engine_enemy_manager_move( enemy, enemy_direction );
				}
			}
		}
	}

	// Execute all commands for this frame.
	//engine_command_manager_execute( frame );


	// Check candy collision before sprite collision as we want to test if all candy eaten = level complete.
	if( coll_type_candy == gamer_collision )
	{
		candy_count = engine_score_manager_get_candy();
		if( lo->level_object_candy_count == candy_count )
		{
			*screen_type = screen_type_pass;
			return;
		}
	}
	else if( coll_type_oneup == gamer_collision )
	{
		engine_audio_manager_sfx_play( sfx_type_power );
	}

	// Kid invincible thus don't check for death collisions.
	if( st->state_object_localcheat )
	{
		*screen_type = screen_type_play;
		return;
	}

	// Kid collide with death tree?
	if( st->state_object_trees_type == tree_type_death )
	{
		if( actor_type_kid != st->state_object_actor_kill )
		{
			*screen_type = screen_type_dead;
			return;
		}
	}

	// Kid collide with Candy Mama?
	gamer_collision = devkit_isCollisionDetected();
	if( 0 != gamer_collision )
	{
		st->state_object_actor_kill = engine_collision_manager_enemy_collision();
		if( actor_type_kid != st->state_object_actor_kill )
		{
			engine_enemy_manager_dead( st->state_object_actor_kill );
			*screen_type = screen_type_dead;
			return;
		}
	}

	*screen_type = screen_type_play;
}