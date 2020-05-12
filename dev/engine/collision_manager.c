#include "collision_manager.h"
//#include "audio_manager.h"
#include "board_manager.h"
#include "enemy_manager.h"
#include "enum_manager.h"
//#include "font_manager.h"
#include "function_manager.h"
#include "gamer_manager.h"
#include "level_manager.h"
#include "move_manager.h"
#include "score_manager.h"
#include "state_manager.h"
#include "tile_manager.h"

#define DISTNACE_EASY		8
#define DISTNACE_HARD		10
static unsigned char collision_distance[] = { DISTNACE_EASY, DISTNACE_HARD };

unsigned char engine_collision_manager_sprite_collision()
{
	struct_gamer_object *go = &global_gamer_object;
	struct_state_object *st = &global_state_object;
	struct_enemy_object *eo;
	unsigned char gamer_collision = actor_type_kid;
	
	unsigned char distance = collision_distance[ st->state_object_difficulty ];
	unsigned char enemy;
	unsigned char dx, dy;

	// TODO delete - used for temp debugging
	//engine_font_manager_draw_data( go->posnX, 2, 0 );
	//engine_font_manager_draw_data( go->posnY, 2, 1 );

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		if( go->posnX > eo->posnX )
		{
			dx = go->posnX - eo->posnX;
		}
		else
		{
			dx = eo->posnX - go->posnX;
		}

		if( go->posnY > eo->posnY )
		{
			dy = go->posnY - eo->posnY;
		}
		else
		{
			dy = eo->posnY - go->posnY;
		}

		if( dx <= distance && dy <= distance )
		{
			gamer_collision = enemy;
			break;
		}
	}

	return gamer_collision;
}

unsigned char engine_collision_manager_tile_collision( unsigned char tile_type )
{
	struct_gamer_object *go = &global_gamer_object;
	struct_state_object *st = &global_state_object;
	unsigned char gamer_collision = coll_type_empty;
	unsigned char erase = 1;			// TODO - use better enum

	// Check gamer collision with candy.
	if( tile_type_candy == tile_type )
	{
		engine_score_manager_update_candy();
		gamer_collision = coll_type_candy;
	}

	// Check gamer collision with trees.
	else if( tile_type_trees == tile_type )
	{
		if( !st->state_object_localcheat && tree_type_death == st->state_object_trees_type )
		{
			gamer_collision = engine_level_manager_get_collision( go->tileX, go->tileY, go->direction, offset_type_none );
			if( coll_type_block == gamer_collision )
			{
				// Edge case : vulnerable Kid inside open exit with death trees...
				gamer_collision = engine_move_manager_inside_exit( go->tileX, go->tileY );
				erase = gamer_collision;
			}
		}
		else
		{
			erase = 0;
		}
	}

	// Check gamer collision with one up.
	else if( tile_type_oneup == tile_type )
	{
		// TODO sound effect...
		//engine_score_manager_update_lives( 1 );
		//engine_audio_manager_sfx_play( sfx_type_power );
		engine_score_manager_update_oneup();
		gamer_collision = coll_type_oneup;
	}

	// Check gamer collision with bonus.
	else if( tile_type_bonusA == tile_type || tile_type_bonusB == tile_type || tile_type_bonusC == tile_type || tile_type_bonusD == tile_type )
	{
		// TODO sound effect...??
		engine_score_manager_update_bonus( tile_type );
	}

	if( erase )
	{
		// Draw blank tile unconditionally.
		engine_tile_manager_draw_blank( SCREEN_TILE_LEFT + ( go->tileX - 1 ) * 2, ( go->tileY - 1 ) * 2 );

		// If death tree on border then do not blank tile!
		if( !st->state_object_localcheat && tree_type_death == st->state_object_trees_type )
		{
			if( tile_type_trees == tile_type )
			{
				if( 1 == go->tileX || 1 == go->tileY || ( MAZE_COLS - 2 ) == go->tileX || ( MAZE_ROWS - 2 ) == go->tileY )
				{
					// Edge case : Do nothing.
					erase = 0;
				}
			}
		}

		if( erase )
		{
			// Otherwise blank tile in all other cases.
			engine_level_manager_blank_tile( go->tileZ );
		}
	}

	return gamer_collision;
}

void engine_collision_manager_reset_death()
{
	struct_gamer_object *go = &global_gamer_object;
	struct_state_object *st = &global_state_object;

	// Kid collided with death tree on border so redraw.
	if( !st->state_object_localcheat && st->state_object_trees_type == tree_type_death )
	{
		if( actor_type_tree == st->state_object_actor_kill )
		{
			if( 1 == go->tileX || 1 == go->tileY || ( MAZE_COLS - 2 ) == go->tileX || ( MAZE_ROWS - 2 ) == go->tileY )
			{
				engine_tile_manager_draw_trees( st->state_object_trees_type, SCREEN_TILE_LEFT + ( go->tileX - 1 ) * 2, ( go->tileY - 1 ) * 2 );
			}
		}
	}
}