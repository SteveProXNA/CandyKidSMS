#include "enemy_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "global_manager.h"
#include "hack_manager.h"
#include "level_manager.h"
#include "memo_manager.h"
#include "move_manager.h"
#include "sprite_manager.h"
#include "state_manager.h"
#include "..\object\board_object.h"
#include "..\object\move_object.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"
#include <stdlib.h>

#define SPRITE_TILES_ENEMY	256 + 48
#define DIRECTION_LOOPING	15

// Global variables.
struct_enemy_object global_enemy_objects[ MAX_ENEMIES ];

static void calcd_frame( unsigned char enemy );
static void calcd_spots( unsigned char enemy );
static void calcd_image( unsigned char enemy, unsigned char image );

// Methods.
void engine_enemy_manager_init()
{
	struct_enemy_object *eo;

	unsigned char frame;
	unsigned char enemy;

	devkit_SMS_mapROMBank( FIXED_BANK );
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];

		eo->tileX = board_object_homeX[ enemy ];
		eo->tileY = board_object_homeY[ enemy ];
		eo->action = enemymove_type_wait;

		eo->paths = 0;
		eo->timer = 0;
		eo->total = 0;
		eo->mover = 1;		// 1=move 0=stay.
		eo->lifecycle = lifecycle_type_idle;
		eo->prev_move = direction_type_none;
		eo->direction = direction_type_none;
		eo->dir_count = 0;
		eo->dir_total = 0;
		eo->dir_total2 = 0;

		eo->image = 0;
		eo->frame = frame_type_stance;

		frame = enemy * NUM_ENTITY_IMAGE * NUM_ENTITY_FRAME + 0;
		eo->images[ 0 ][ 0 ] = enemy_object_image[ frame + 0 ];
		eo->images[ 0 ][ 1 ] = enemy_object_image[ frame + 1 ];
		eo->images[ 1 ][ 0 ] = enemy_object_image[ frame + 2 ];
		eo->images[ 1 ][ 1 ] = enemy_object_image[ frame + 3 ];
		eo->scatter[ 0 ] = enemy; eo->scatter[ 1 ] = enemy; eo->scatter[ 2 ] = enemy; eo->scatter[ 3 ] = enemy;

		calcd_frame( enemy );
		calcd_spots( enemy );
	}
}

void engine_enemy_manager_load()
{
	struct_state_object *st = &global_state_object;
	struct_enemy_object *eo;
	unsigned char enemy;
	unsigned char actor;
	unsigned char check;
	unsigned char index;
	unsigned char count = MAX_ENEMIES + st->state_object_difficulty;
	unsigned char delta;
	unsigned char offset;
	unsigned char random = st->state_object_round_data + 2;

	engine_state_manager_fight( fight_type_enemy );
	engine_enemy_manager_stance();

	devkit_SMS_mapROMBank( FIXED_BANK );
	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		if( !eo->mover )
		{
			continue;
		}

		eo->loops = 0;

		// Determine scatter tiles.
		check = enemy;
		for( index = 0; index < NUM_DIRECTIONS; index++ )
		{
			while( 1 )
			{
				actor = rand() % count;
				if( 0 == index )
				{
					if( actor == enemy || actor_type_kid == actor )
					{
						continue;
					}
				}
				else
				{
					if( check == actor )
					{
						continue;
					}
				}

				eo->scatter[ index ] = actor;
				check = actor;
				break;
			}
		}

		// Determine interval that Mama hands swap.
		index = 4 * enemy + st->state_object_difficulty * 2 + st->state_object_pace_speed;
		eo->hands = 0;
		eo->swaps = enemy_object_hands[ index ];
		delta = rand() % random;
		eo->swaps -= delta;


		// Determine interval at start of level Mama waits.
		index = 4 * enemy + st->state_object_difficulty * 2 + st->state_object_pace_speed;
		eo->waiter = enemy_object_waits[ index ];
		delta = rand() % random;
		eo->waiter -= delta;

		// Determine interval Mama toggles from scatter to attack mode.
		eo->toggle[ enemymove_type_tour ] = enemy_object_tours[ index ];
		delta = rand() % random;
		eo->toggle[ enemymove_type_tour ] -= delta;

		eo->toggle[ enemymove_type_kill ] = enemy_object_kills[ index ];
		delta = rand() % random;
		eo->toggle[ enemymove_type_kill ] += delta;

		eo->ticker = 0;
		eo->dir_count = 0;
		eo->dir_total = 0;
		eo->dir_total2 = 0;
		eo->action = enemymove_type_wait;

		// Mix up the order depending on Mama enemy.
		index = 8 * enemy + st->state_object_difficulty * 2 + st->state_object_pace_speed;
		eo->speeds[ 0 ] = enemy_object_speed[ index + 0 ];
		eo->delays[ 0 ] = enemy_object_delay[ index + 0 ];
		eo->speeds[ 1 ] = enemy_object_speed[ index + 4 ];
		eo->delays[ 1 ] = enemy_object_delay[ index + 4 ];


		offset = enemy;
		if( actor_type_suz == enemy )
		{
			offset = rand() % 2;
		}

		eo->speeds[ offset ] = enemy_object_speed[ index + 0 ];
		eo->delays[ offset ] = enemy_object_delay[ index + 0 ];

		offset = 1 - offset;
		eo->speeds[ offset ] = enemy_object_speed[ index + 4 ];
		eo->delays[ offset ] = enemy_object_delay[ index + 4 ];

		eo->speed = eo->speeds[ 0 ];
		eo->delay = eo->delays[ 0 ];
	}
}

void engine_enemy_manager_stance()
{
	struct_enemy_object *eo;
	unsigned char enemy;

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		eo->frame = frame_type_stance;
		calcd_frame( enemy );
	}
}


void engine_enemy_manager_dohand( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->hands++;
	if( eo->hands < eo->swaps )
	{
		return;
	}

	eo->hands = 0;
	eo->frame = 1 - eo->frame;
	calcd_frame( enemy );
}


void engine_enemy_manager_update( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	if( lifecycle_type_move != eo->lifecycle )
	{
		return;
	}

	eo->timer++;
	if( eo->timer < eo->delay )
	{
		return;
	}

	eo->timer = 0;
	eo->total += eo->speed;

	// Update position.
	if( direction_type_upxx == eo->direction )
	{
		eo->posnY -= eo->speed;
	}
	else if( direction_type_down == eo->direction )
	{
		eo->posnY += eo->speed;
	}
	else if( direction_type_left == eo->direction )
	{
		eo->posnX -= eo->speed;
	}
	else if( direction_type_rght == eo->direction )
	{
		eo->posnX += eo->speed;
	}

	// Update lifecycle.
	if( eo->total >= TILE_SIZE )
	{
		if( direction_type_upxx == eo->direction )
		{
			eo->tileY--;
		}
		else if( direction_type_down == eo->direction )
		{
			eo->tileY++;
		}
		else if( direction_type_left == eo->direction )
		{
			eo->tileX--;
		}
		else if( direction_type_rght == eo->direction )
		{
			eo->tileX++;
		}

		calcd_spots( enemy );

		eo->lifecycle = lifecycle_type_idle;
		eo->total = 0;
	}
}



void engine_enemy_manager_draw()
{
	struct_enemy_object *eo;
	unsigned char enemy;

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		engine_sprite_manager_draw_entity( eo->posnX, eo->posnY, eo->calcd );
	}
}

void engine_enemy_manager_draws( unsigned char enemy, unsigned char x, unsigned char y )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	engine_sprite_manager_draw_entity( x, y, eo->calcd );
}

void engine_enemy_manager_hide()
{
	struct_enemy_object *eo;
	unsigned char enemy;

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		if( eo->posnX > 60 && eo->posnX < 148 && eo->posnY >60 && eo->posnY < 116 )
		{
			continue;
		}

		engine_sprite_manager_draw_entity( eo->posnX, eo->posnY, eo->calcd );
	}
}

void engine_enemy_manager_move( unsigned char enemy, unsigned char direction )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->lifecycle = lifecycle_type_move;
	eo->direction = direction;
}

void engine_enemy_manager_pace( unsigned char enemy, unsigned char boost )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->speed = eo->speeds[ boost ];
	eo->delay = eo->delays[ boost ];
}

void engine_enemy_manager_stop( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];

	eo->dir_count++;
	eo->dir_total += eo->direction;
	eo->prev_move = eo->direction;
	eo->direction = direction_type_none;
	eo->ticker++;
	calcd_frame( enemy );
}

void engine_enemy_manager_dead( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->lifecycle = lifecycle_type_dead;
	eo->prev_move = eo->direction;
	eo->direction = direction_type_none;
}

void engine_enemy_manager_reset_home()
{
	struct_enemy_object *eo;
	unsigned char enemy;

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];

		// Reset at home.
		eo->tileX = board_object_homeX[ enemy ];
		eo->tileY = board_object_homeY[ enemy ];
		calcd_spots( enemy );

		eo->lifecycle = lifecycle_type_idle;
		eo->direction = direction_type_none;
		eo->frame = frame_type_stance;
		eo->total = 0;
		calcd_frame( enemy );
	}
}

void engine_enemy_manager_reset_mode( unsigned char enemy, unsigned char mode )
{
	struct_state_object *st = &global_state_object;
	struct_hack_object *ho = &global_hack_object;
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->action = mode;
	eo->ticker = 0;
	eo->dir_count = 0;
	eo->dir_total = 0;
	eo->dir_total2 = 0;

	// Reset speed and delay to the correct mode.
	eo->speed = eo->speeds[ mode ];
	eo->delay = eo->delays[ mode ];

	if( ho->hack_object_mydebugger )
	{
		engine_memo_manager_debugging( enemy, eo->action );
	}
}

void engine_enemy_manager_frame( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->frame = 1 - eo->frame;
	calcd_frame( enemy );
}

void engine_enemy_manager_image( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->image = 1 - eo->image;
	calcd_frame( enemy );
}

void engine_enemy_manager_images( unsigned char image_pro, unsigned char image_adi, unsigned char image_suz )
{
	calcd_image( actor_type_pro, image_pro );
	calcd_image( actor_type_adi, image_adi );
	calcd_image( actor_type_suz, image_suz );
}


unsigned char engine_enemy_manager_scatter_direction( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	unsigned char enemy_direction = direction_type_none;
	unsigned char targetX;
	unsigned char targetY;
	unsigned char advance;
	unsigned char actor;

	// SCATTER.
	actor = eo->scatter[ eo->paths ];
	targetX = board_object_homeX[ actor ];
	targetY = board_object_homeY[ actor ];


	// Attempt to prevent looping.
	advance = 0;
	if( NUM_DIRECTIONS == eo->dir_count && DIRECTION_LOOPING == eo->dir_total )
	{
		eo->dir_total2++;
		advance = 1;
	}
	else
	{
		advance = targetX == eo->tileX && targetY == eo->tileY;
	}

	if( NUM_DIRECTIONS == eo->dir_count )
	{
		eo->dir_count = 0;
		eo->dir_total = 0;
	}


	if( advance )
	{
		eo->paths++;
		if( eo->paths >= NUM_DIRECTIONS )
		{
			eo->paths = 0;
		}

		actor = eo->scatter[ eo->paths ];
		targetX = board_object_homeX[ actor ];
		targetY = board_object_homeY[ actor ];
	}

	enemy_direction = engine_move_manager_what_direction( eo->tileX, eo->tileY, eo->prev_move, targetX, targetY );
	return enemy_direction;
}

unsigned char engine_enemy_manager_gohome_direction( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	unsigned char enemy_direction = direction_type_none;

	unsigned char targetX;
	unsigned char targetY;

	// GO HOME.
	targetX = board_object_homeX[ enemy ];
	targetY = board_object_homeY[ enemy ];

	// If enemy at home tile then just stop.
	if( targetX == eo->tileX && targetY == eo->tileY )
	{
		return direction_type_none;
	}

	enemy_direction = engine_move_manager_what_direction( eo->tileX, eo->tileY, eo->prev_move, targetX, targetY );
	return enemy_direction;
}

unsigned char engine_enemy_manager_attack_direction( unsigned char enemy, unsigned char targetX, unsigned char targetY )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	struct_enemy_object *eo0;

	unsigned char enemy_direction = direction_type_none;

	// Attempt to prevent looping.
	if( NUM_DIRECTIONS == eo->dir_count && DIRECTION_LOOPING == eo->dir_total )
	{
		eo->dir_total2++;
	}

	if( NUM_DIRECTIONS == eo->dir_count )
	{
		eo->dir_count = 0;
		eo->dir_total = 0;
	}

	// ATTACK.
	if( actor_type_pro == enemy )
	{
		enemy_direction = engine_move_manager_what_direction( eo->tileX, eo->tileY, eo->prev_move, targetX, targetY );
	}
	else if( actor_type_adi == enemy )
	{
		// Look two tiles in front on Candy Kid.
		engine_level_manager_get_next_index( &targetX, &targetY, eo->prev_move, offset_type_two );
		enemy_direction = engine_move_manager_what_direction( eo->tileX, eo->tileY, eo->prev_move, targetX, targetY );
	}
	else if( actor_type_suz == enemy )
	{
		// Try Pacman algorithm based off Blinky [Pro]
		eo0 = &global_enemy_objects[ actor_type_pro ];

		targetX = eo0->tileX;
		targetY = eo0->tileY;

		// Look four tiles in front on Candy Kid.
		engine_level_manager_get_next_index( &targetX, &targetY, direction_type_none, offset_type_none );

		targetX = ( offset_type_four - 1 ) - targetX;
		targetY = ( offset_type_four - 1 ) - targetY;
		enemy_direction = engine_move_manager_what_direction( eo->tileX, eo->tileY, eo->prev_move, targetX, targetY );
	}

	return enemy_direction;
}


unsigned char engine_enemy_manager_input_boost( unsigned char enemy )
{
	struct_state_object *st = &global_state_object;
	struct_hack_object *ho = &global_hack_object;
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	unsigned char toggle = eo->toggle[ eo->action ];
	unsigned char boost = 0;
	unsigned char reset = 0;

	// Attempt to prevent infinite looping by toggling action.
	if( eo->dir_total2 >= ENEMY_LOOPS )
	{
		reset = 1;
	}

	// Not ready to swap modes.
	if( !reset )
	{
		if( eo->ticker < toggle )
		{
			return pace_type_none;
		}
	}

	eo->action = 1 - eo->action;		// disable for testing.
	eo->ticker = 0;
	eo->dir_count = 0;
	eo->dir_total = 0;
	eo->dir_total2 = 0;
	boost = eo->action;

	if( ho->hack_object_mydebugger )
	{
		engine_memo_manager_debugging( enemy, eo->action );
	}

	return boost;
}


static void calcd_frame( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->calcd = SPRITE_TILES_ENEMY + eo->images[ eo->image ][ eo->frame ];
}
static void calcd_spots( unsigned char enemy )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->posnX = board_object_posnX[ eo->tileX ];
	eo->posnY = board_object_posnY[ eo->tileY ];
	engine_function_manager_convertXYtoZ( MAZE_ROWS, eo->tileX, eo->tileY, &eo->tileZ );
}
static void calcd_image( unsigned char enemy, unsigned char image )
{
	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
	eo->image = image;
	calcd_frame( enemy );
}