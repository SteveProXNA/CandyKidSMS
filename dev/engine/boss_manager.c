#include "boss_manager.h"
#include "enemy_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "gamer_manager.h"
#include "move_manager.h"
#include "sprite_manager.h"
#include "state_manager.h"
#include "..\object\board_object.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"
#include <stdlib.h>

// IMPORTANT disable compiler warning 110
#ifdef _CONSOLE
#else
	#pragma disable_warning 110
	#pragma disable_warning 126
#endif

// Global variables.
struct_boss_object global_boss_objects[ MAX_BOSSES ];

static void calcd_spots( unsigned char index );
static unsigned char boss_index[ MAX_BOSSES ] = { 0, 0 };
static unsigned char boss_one;
static unsigned char boss_two;
static unsigned char content_index;

void engine_boss_manager_init()
{
	struct_boss_object *bo;
	unsigned char bossX;

	for( bossX = 0; bossX < MAX_BOSSES; bossX++ )
	{
		bo = &global_boss_objects[ bossX ];

		bo->actor = 0;
		bo->posnX = 0;	bo->posnY = 0;
		bo->homeX = 0;	bo->homeY = 0;
		bo->tileX = 0;	bo->tileY = 0;	bo->tileZ = 0;
		bo->waiter = 0;	bo->action = enemymove_type_wait;

		bo->paths = 0;	bo->timer = 0;
		//bo->delta = 0;
		bo->total = 0;

		bo->sizer = boss_type_large;
		bo->mover = 1;	bo->drawr = 1;
		bo->high = 0;	bo->wide = 0;

		bo->lifecycle = lifecycle_type_idle;
		bo->prev_move = direction_type_none;
		bo->direction = direction_type_none;

		bo->image = 0;
	}

	boss_one = 0; boss_two = 0;
	content_index = 0;
}

void engine_boss_manager_setup( unsigned char round )
{
	// Rule:
	// boss1	every  2nd round
	// boss2	every 10th round
	struct_enemy_object *eo;
	unsigned char enemy;
	unsigned char image;

	// Randomize the first boss.
	enemy = rand() % MAX_ENEMIES;
	boss_index[ 0 ] = enemy;
	boss_one = enemy;
	if( 0 == ( round + 1 ) % MAX_ROUNDS )
	{
		engine_state_manager_fight( fight_type_boss1 );
		boss_index[ 1 ] = enemy;
		boss_two = enemy;

		eo = &global_enemy_objects[ enemy ];
		image = eo->image;

		content_index = MAX_ENEMIES + enemy * 2 + image;
	}
	else
	{
		engine_state_manager_fight( fight_type_boss2 );

		// Randomize the second boss.
		while( 1 )
		{
			enemy = rand() % MAX_ENEMIES;
			if( boss_one != enemy )
			{
				boss_index[ 1 ] = enemy;
				boss_two = enemy;
				break;
			}
		}

		if( ( actor_type_pro == boss_one && actor_type_adi == boss_two ) || ( actor_type_adi == boss_one && actor_type_pro == boss_two ) )
		{
			content_index = 0;
		}
		else if( ( actor_type_adi == boss_one && actor_type_suz == boss_two ) || ( actor_type_suz == boss_one && actor_type_adi == boss_two ) )
		{
			content_index = 1;
		}
		else if( ( actor_type_pro == boss_one && actor_type_suz == boss_two ) || ( actor_type_suz == boss_one && actor_type_pro == boss_two ) )
		{
			content_index = 2;
		}
	}
}

void engine_boss_manager_load()
{
	struct_state_object *st = &global_state_object;
	struct_gamer_object *go = &global_gamer_object;
	struct_enemy_object *eo;
	
	struct_boss_object *bo;
	unsigned char bossX;
	unsigned char enemy;
	unsigned char index;

	unsigned char minX, minY;
	//unsigned char maxX, maxY;
	unsigned char distX, distY;
	unsigned char tileX, tileY, tileZ;

	// Used to calculate random scatter tiles.
	eo = &global_enemy_objects[ actor_type_pro ];
	minX = go->tileX + 1 - st->state_object_fight_type;
	minY = go->tileY + 1 - st->state_object_fight_type;

	distX = 10;
	distY = 7;
	if( fight_type_boss1 == st->state_object_fight_type )
	{
		distX = 7;
		distY = 5;
	}

	devkit_SMS_mapROMBank( FIXED_BANK );
	for( bossX = 0; bossX < MAX_BOSSES; bossX++ )
	{
		bo = &global_boss_objects[ bossX ];
		bo->actor = boss_index[ bossX ];

		bo->homeX = board_object_homeX[ bo->actor ];
		bo->homeY = board_object_homeY[ bo->actor ];

		// Offset homeY by 1x row for bottom bosses.
		if( actor_type_suz != bo->actor )
		{
			bo->homeY -= 1;
		}

		bo->tileX = bo->homeX;
		bo->tileY = bo->homeY;

		bo->mover = 1;
		bo->drawr = 1;
		bo->wide = 0;
		bo->high = 0;

		if( fight_type_boss1 == st->state_object_fight_type )
		{
			bo->sizer = boss_type_large;
			if( 1 == bossX )
			{
				bo->mover = 0;
				bo->drawr = 0;
			}
		}
		else if( fight_type_boss2 == st->state_object_fight_type )
		{
			bo->sizer = boss_type_small;

			// Temporary only 1x small boss
			if( 1 == bossX )
			{
				bo->mover = 0;
				bo->drawr = 0;
			}

			eo = &global_enemy_objects[ bo->actor ];
			bo->wide = eo->image;
			if( ( actor_type_pro == bo->actor ) || ( actor_type_adi == bo->actor && 1 == content_index ) )
			{
				bo->high = 0;
			}
			else if( ( actor_type_suz == bo->actor ) || ( actor_type_adi == bo->actor && 0 == content_index ) )
			{
				bo->high = 1;
			}
		}

		calcd_spots( bossX );

		// Bosses will NOT wait.
		bo->action = enemymove_type_tour;

		enemy = bo->actor;
		index = ( 8 * enemy ) + ( 4 * ( st->state_object_fight_type - 1 ) ) + ( st->state_object_difficulty * 2 ) + st->state_object_pace_speed;

		bo->speed = boss_object_speed[ index ];
		bo->delay = boss_object_delay[ index ];

		// Scatter.
		for( index = 0; index < NUM_DIRECTIONS * 2; index ++ )
		{
			tileX = rand() % distX;
			tileY = rand() % distY;

			// Edge case for big boss!
			if( 0 == tileX && fight_type_boss1 == st->state_object_fight_type )
			{
				tileX = 1;
			}

			tileX += minX;
			tileY += minY;
			engine_function_manager_convertXYtoZ( MAZE_ROWS, tileX, tileY, &tileZ );
			bo->scatter[ index ] = tileZ;
		}
	}
}

void engine_boss_manager_update( unsigned char bossX )
{
	struct_boss_object *bo = &global_boss_objects[ bossX ];
	if( lifecycle_type_move != bo->lifecycle )
	{
		return;
	}

	bo->timer++;
	if( bo->timer < bo->delay )
	{
		return;
	}

	bo->timer = 0;
	bo->total += bo->speed;

	// Update position.
	if( direction_type_upxx == bo->direction )
	{
		bo->posnY -= bo->speed;
	}
	else if( direction_type_down == bo->direction )
	{
		bo->posnY += bo->speed;
	}
	else if( direction_type_left == bo->direction )
	{
		bo->posnX -= bo->speed;
	}
	else if( direction_type_rght == bo->direction )
	{
		bo->posnX += bo->speed;
	}

	// Update lifecycle.
	if( bo->total >= TILE_SIZE )
	{
		if( direction_type_upxx == bo->direction )
		{
			bo->tileY--;
		}
		else if( direction_type_down == bo->direction )
		{
			bo->tileY++;
		}
		else if( direction_type_left == bo->direction )
		{
			bo->tileX--;
		}
		else if( direction_type_rght == bo->direction )
		{
			bo->tileX++;
		}

		calcd_spots( bossX );

		bo->lifecycle = lifecycle_type_idle;
		bo->total = 0;
	}
}

void engine_boss_manager_draw()
{
	struct_boss_object *bo;
	unsigned char bossX;

	for( bossX = 0; bossX < MAX_BOSSES; bossX++ )
	{
		bo = &global_boss_objects[ bossX ];
		if( bo->drawr )
		{
			if( boss_type_large == bo->sizer )
			{
				engine_sprite_manager_draw_boss1( bo->posnX, bo->posnY );
			}
			else if( boss_type_small == bo->sizer )
			{
				engine_sprite_manager_draw_boss2( bo->wide, bo->high, bo->posnX, bo->posnY );
			}
		}
	}
}

void engine_boss_manager_hide()
{
	struct_boss_object *bo;
	unsigned char bossX;

	for( bossX = 0; bossX < MAX_BOSSES; bossX++ )
	{
		bo = &global_boss_objects[ bossX ];
		if( bo->drawr )
		{
			if( boss_type_large == bo->sizer )
			{
				if( bo->posnX > 30 && bo->posnX < 146 && bo->posnY > 16 && bo->posnY < 112 )
				{
					continue;
				}

				engine_sprite_manager_draw_boss1( bo->posnX, bo->posnY );
			}
			else if( boss_type_small == bo->sizer )
			{
				if( bo->posnX > 54 && bo->posnX < 146 && bo->posnY > 48 && bo->posnY < 112 )
				{
					continue;
				}

				engine_sprite_manager_draw_boss2( bo->wide, bo->high, bo->posnX, bo->posnY );
			}
		}
	}
}

void engine_boss_manager_move( unsigned char bossX, unsigned char direction )
{
	struct_boss_object *bo = &global_boss_objects[ bossX ];
	bo->lifecycle = lifecycle_type_move;
	bo->direction = direction;
}

void engine_boss_manager_stop( unsigned char bossX )
{
	struct_boss_object *bo = &global_boss_objects[ bossX ];
	bo->prev_move = bo->direction;
	bo->direction = direction_type_none;
}

void engine_boss_manager_dead( unsigned char bossX )
{
	struct_boss_object *bo = &global_boss_objects[ bossX ];
	bo = &global_boss_objects[ bossX ];
	bo->lifecycle = lifecycle_type_dead;
	bo->prev_move = bo->direction;
	bo->direction = direction_type_none;
}

void engine_boss_manager_reset_home()
{
	struct_boss_object *bo;
	unsigned char bossX;

	for( bossX = 0; bossX < MAX_BOSSES; bossX++ )
	{
		bo = &global_boss_objects[ bossX ];
		if( !bo->mover )
		{
			continue;
		}

		// Reset at home.
		bo->tileX = bo->homeX;
		bo->tileY = bo->homeY;
		calcd_spots( bossX );

		bo->lifecycle = lifecycle_type_idle;
		bo->direction = direction_type_none;
		bo->total = 0;
	}
}

unsigned char engine_boss_manager_scatter_direction( unsigned char bossX )
{
	struct_boss_object *bo = &global_boss_objects[ bossX ];
	unsigned char bossX_direction = direction_type_none;
	unsigned char targetX;
	unsigned char targetY;
	unsigned char advance;
	unsigned char tileZ;

	// SCATTER.
	tileZ = bo->scatter[ bo->paths ];
	engine_function_manager_convertZtoXY( MAZE_ROWS, tileZ, &targetX, &targetY );

	advance = targetX == bo->tileX && targetY == bo->tileY;
	if( advance )
	{
		bo->paths++;
		if( bo->paths >= NUM_DIRECTIONS * 2 )
		{
			bo->paths = 0;
		}

		tileZ = bo->scatter[ bo->paths ];
		engine_function_manager_convertZtoXY( MAZE_ROWS, tileZ, &targetX, &targetY );
	}

	bossX_direction = engine_move_manager_what_direction( bo->tileX, bo->tileY, bo->prev_move, targetX, targetY );
	return bossX_direction;
}

unsigned char engine_boss_manager_gohome_direction( unsigned char bossX )
{
	struct_boss_object *bo = &global_boss_objects[ bossX ];
	unsigned char bossX_direction = direction_type_none;

	unsigned char targetX = bo->homeX;
	unsigned char targetY = bo->homeY;


	// If bossX at home tile then just stop.
	if( targetX == bo->tileX && targetY == bo->tileY )
	{
		return direction_type_none;
	}

	bossX_direction = engine_move_manager_what_direction( bo->tileX, bo->tileY, bo->prev_move, targetX, targetY );
	return bossX_direction;
}

void engine_boss_manager_content()
{
	unsigned char *tiles;
	unsigned char *color;
	unsigned char bank;

	devkit_SMS_mapROMBank( FIXED_BANK );
	tiles = ( unsigned char* ) boss_object_tiles[ content_index ];
	color = ( unsigned char* ) boss_object_color[ content_index ];
	bank = boss_object_bank[ content_index ];

	devkit_SMS_mapROMBank( bank );
	devkit_SMS_loadPSGaidencompressedTiles( tiles, SPRITE_TILES );
	devkit_SMS_loadSpritePalette( ( void * ) color );
}

unsigned char engine_boss_manager_index()
{
	return content_index;
}

static void calcd_spots( unsigned char index )
{
	struct_boss_object *bo = &global_boss_objects[ index ];
	bo->posnX = board_object_posnX[ bo->tileX ];
	bo->posnY = board_object_posnY[ bo->tileY ];

	if( boss_type_large == bo->sizer )
	{
		bo->posnX -= TILE_WIDE;
		bo->posnY -= TILE_HIGH;
	}
	if( boss_type_small == bo->sizer )
	{
		bo->posnX -= TILE_HALF / 2;
	}

	engine_function_manager_convertXYtoZ( MAZE_ROWS, bo->tileX, bo->tileY, &bo->tileZ );
}