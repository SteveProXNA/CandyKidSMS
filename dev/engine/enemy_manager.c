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
		//eo->actor = enemy;

		eo->tileX = board_object_homeX[ enemy ];
		eo->tileY = board_object_homeY[ enemy ];
		eo->action = enemymove_type_wait;

		eo->paths = 0;
		eo->timer = 0;
//		eo->delta = 0;
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

		// todo DELETE stevepro
		//eo->scatter[ 0 ] = 1;
		//eo->scatter[ 1 ] = 3;
		//eo->scatter[ 2 ] = 2;
		//eo->scatter[ 3 ] = 0;

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


		// TODO delete this - debugging
		//engine_font_manager_draw_data( eo->speed, 10, 0 );
		//engine_font_manager_draw_data( eo->delay, 10, 1 );

		//engine_font_manager_draw_data( eo->waiter, 18, 0 );
		//engine_font_manager_draw_data( eo->toggle[ 0 ], 25, 0 );
		//engine_font_manager_draw_data( eo->toggle[ 1 ], 25, 1 );
		//engine_font_manager_draw_data( eo->speeds, 20, 0 );
		//engine_font_manager_draw_data( eo->delays, 20, 1 );

		//engine_font_manager_draw_data( eo->speeds[ 0 ], 10, 0 );
		//engine_font_manager_draw_data( eo->delays[ 0 ], 10, 1 );
		//engine_font_manager_draw_data( eo->speeds[ 1 ], 20, 0 );
		//engine_font_manager_draw_data( eo->delays[ 1 ], 20, 1 );
		// TODO delete this - debugging
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
//	eo->delta += eo->speed;
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
//		eo->delta = 0;
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
	//unsigned char toggle;

	//eo->prev_move[ 3 ] = eo->prev_move[ 2 ];
	//eo->prev_move[ 2 ] = eo->prev_move[ 1 ];
	//eo->prev_move[ 1 ] = eo->prev_move[ 0 ];
	//eo->prev_move[ 0 ] = eo->direction;
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
	//eo->frame = frame_type_stance;
	//calcd_frame( enemy );
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
		//eo->delta = 0;
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


// TODO delete!!
void engine_enemy_manager_debug()
{
	struct_hack_object *ho = &global_hack_object;
	struct_enemy_object *eo;
	unsigned char enemy;

	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
	{
		eo = &global_enemy_objects[ enemy ];
		eo->mover = !ho->hack_object_enemy_move[ enemy ];
	}
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


	//if( targetX == eo->tileX && targetY == eo->tileY )
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

	//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
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

	//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
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
		//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
		enemy_direction = engine_move_manager_what_direction( eo->tileX, eo->tileY, eo->prev_move, targetX, targetY );
	}
	else if( actor_type_adi == enemy )
	{
		// Look two tiles in front on Candy Kid.
		engine_level_manager_get_next_index( &targetX, &targetY, eo->prev_move, offset_type_two );
		//enemy_direction = engine_enemy_manager_what_direction( enemy, targetX, targetY );
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
		//enemy_direction = engine_enemy_manager_what_direction( enemy, ( offset_type_four - 1 ) - targetX, ( offset_type_four - 1 ) - targetY );
		enemy_direction = engine_move_manager_what_direction( eo->tileX, eo->tileY, eo->prev_move, targetX, targetY );
	}

	return enemy_direction;
}


// TODO delete - this is now generic function in the move manager
//unsigned char engine_enemy_manager_what_direction( unsigned char enemy, unsigned char targetX, unsigned char targetY )
//{
//	struct_enemy_object *eo = &global_enemy_objects[ enemy ];
//	unsigned char directions[ NUM_DIRECTIONS ] = { direction_type_none, direction_type_none, direction_type_none, direction_type_none };
//	unsigned char move_direction = direction_type_none;
//	unsigned char oppX_direction = direction_type_none;
//	//unsigned char prev_direction = direction_type_none;
//	unsigned char test_direction = direction_type_none;
//	unsigned char collision = direction_type_none;
//	unsigned char available = direction_type_none;
//
//	unsigned char sourceX = eo->tileX;
//	unsigned char sourceY = eo->tileY;
//	unsigned char index = 0;
//	//unsigned char byte = 0;
//	unsigned char list = 0;
//	unsigned char half = 0;
//	unsigned char flip = 0;
//
//	// Get the list of 4x possible directions in the order depending on tiles.
//	engine_move_manager_get_directions( sourceX, sourceY, targetX, targetY, &list, &half );
//
//	index = list * 2 * NUM_DIRECTIONS + half * NUM_DIRECTIONS;
//
//	// TODO fixed bank - change to data bank!!
//	//directions[ 0 ] = enemy_object_directions[ index + 0 ];
//	//directions[ 1 ] = enemy_object_directions[ index + 1 ];
//	//directions[ 2 ] = enemy_object_directions[ index + 2 ];
//	//directions[ 3 ] = enemy_object_directions[ index + 3 ];
//	directions[ 0 ] = move_object_directions[ index + 0 ];
//	directions[ 1 ] = move_object_directions[ index + 1 ];
//	directions[ 2 ] = move_object_directions[ index + 2 ];
//	directions[ 3 ] = move_object_directions[ index + 3 ];
//
//	//prev_direction = eo->prev_move[ 3 ];
//	//oppX_direction = engine_move_manager_opposite_direction( eo->prev_move[ 0 ] );
//	oppX_direction = engine_move_manager_opposite_direction( eo->prev_move );
//	available = engine_level_manager_get_direction( sourceX, sourceY, direction_type_none, offset_type_none );
//
//	for( index = 0; index < NUM_DIRECTIONS; index++ )
//	{
//		test_direction = directions[ index ];
//		if( oppX_direction == test_direction )
//		{
//			continue;
//		}
//
//		if( test_direction == ( available & test_direction ) )
//		{
//			move_direction = test_direction;
//			break;
//		}
//
//		//collision = engine_level_manager_get_collision( sourceX, sourceY, test_direction, offset_type_one );
//		//if( coll_type_empty == collision )
//		//{
//		//	move_direction = test_direction;
//		//	break;
//		//}
//	}
//
//	// TODO delete as back up of the code...
//	//oppX_direction = engine_move_manager_opposite_direction( eo->prev_move );
//	//for( index = 0; index < NUM_DIRECTIONS; index++ )
//	//{
//	//	test_direction = directions[ index ];
//	//	if( oppX_direction != test_direction )
//	//	{
//	//		//if( prev_direction != test_direction )
//	//		//{
//	//			collision = engine_level_manager_get_collision( sourceX, sourceY, test_direction, offset_type_one );
//	//			if( coll_type_empty == collision )
//	//			{
//	//				move_direction = test_direction;
//	//				break;
//	//			}
//	//		//}
//	//	}
//	//}
//
//	// Enemy in cul de sac so must be able to go in opposite direction!
//	if( direction_type_none == move_direction )
//	{
//		move_direction = oppX_direction;
//	}
//
//	return move_direction;
//}

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

	// TODO delete - loose grip on Attack action only.
	//if( enemymove_type_kill == eo->action && eo->dir_total2 >= ENEMY_LOOPS )
	//{
	//	reset = 1;
	//}

	// Not ready to swap modes.
	if( !reset )
	{
		if( eo->ticker < toggle )
		{
			return pace_type_none;
		}
	}

	eo->action = 1 - eo->action;		// stevepro disable for testing.		ADRIANA
	eo->ticker = 0;
	eo->dir_count = 0;
	eo->dir_total = 0;
	eo->dir_total2 = 0;
	boost = eo->action;

	// IMPORTANT - this will alternate the images during game play - useful for debugging Scatter vs. Attack mode
	// Swap image to indicate different mode : Scatter vs. Attack.
	//if( st->state_object_mydebugger )
	//{
	//	eo->image = 1 - eo->image;
	//	calcd_frame( enemy );
	//}
	// IMPORTANT - this will alternate the images during game play - useful for debugging Scatter vs. Attack mode


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