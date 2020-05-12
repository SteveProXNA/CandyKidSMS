//#include "credit_screen.h"
////#include "..\engine\asm_manager.h"
////#include "..\engine\audio_manager.h"
////#include "..\engine\board_manager.h"
////#include "..\engine\boss_manager.h"
////#include "..\engine\content_manager.h"
////#include "..\engine\collision_manager.h"
//#include "..\engine\enum_manager.h"
////#include "..\engine\font_manager.h"
////#include "..\engine\gamer_manager.h"
////#include "..\engine\global_manager.h"
////#include "..\engine\input_manager.h"
////#include "..\engine\level_manager.h"
////#include "..\engine\locale_manager.h"
////#include "..\engine\main_manager.h"
////#include "..\engine\memo_manager.h"
////#include "..\engine\option_manager.h"
////#include "..\engine\score_manager.h"
//////#include "..\engine\sprite_manager.h"
//#include "..\engine\state_manager.h"
////#include "..\engine\tile_manager.h"
////#include "..\engine\timer_manager.h"
////#include "..\devkit\_sms_manager.h"
////#include "..\object\level_object.h"
//
////static unsigned char first_time;
////static unsigned char nextr_direction;
//
//void screen_credit_screen_load()
//{
//	//struct_state_object *st = &global_state_object;
//	////struct_level_object *lo = &global_level_object;
//	////unsigned char oneup_count = 2;
//
//	//// Load from SRAM first.
//	//engine_main_manager_load();
//
//
//	//engine_asm_manager_clear_VRAM();
//	//engine_content_manager_load_tiles_font();
//	//engine_content_manager_load_tiles_game();
//
//	//
//	//engine_board_manager_border( border_type_game );
//	//engine_board_manager_side_tile();
//
//		// TODO delete
//	// Reset all score data.
//	//engine_score_manager_text();
//	//engine_score_manager_init();
//	//engine_memo_manager_option();
//	// TODO delete
//
//
//	//// load screen
//	//// Reset all score data.
//	//engine_score_manager_load();
//
//	////engine_boss_manager_reset_home()
//	//engine_gamer_manager_reset();
//
//	//// Force override enemy move!
//	////engine_enemy_manager_debug();
//
//	//engine_gamer_manager_load();
//	//engine_boss_manager_load();
//
//	//// load oneup
//	//engine_level_manager_clear();
//	//engine_level_manager_load_oneup( oneup_count );
//
//	//engine_level_manager_draw_level();
//	//engine_level_manager_draw_middle();
//	//
//
//	//engine_delay_manager_load( 0 );
//
//	////	engine_command_manager_load();
//	//engine_frame_manager_load();
//
//	//engine_frame_manager_draw();
//	//engine_delay_manager_draw();
//
//
//	//nextr_direction = direction_type_none;
//	//engine_reset_manager_load( QUIT_SCREEN_DELAY );
//
//
//	////st->state_object_next_screen = screen_type_init;
//	//st->state_object_curr_screen = screen_type_credit;
//
//
//	//engine_font_manager_draw_text( "CREDIT SCREEN...!!", 4, 10 );
//	//engine_font_manager_draw_data( lo->level_object_oneup_count, 10, 12 );
//}
//
//void screen_credit_screen_update( unsigned char *screen_type )
//{
//	//struct_frame_object *fo = &global_frame_object;
//	//struct_gamer_object *go = &global_gamer_object;
//	struct_state_object *st = &global_state_object;
//	//struct_level_object *lo = &global_level_object;
//	////struct_boss_object *bo;
//
//	//unsigned char gamer_boost = 0;
//	//unsigned char enemy_boost = 0;
//	//unsigned char gamer_direction = direction_type_none;
//	//unsigned char bossX_direction = direction_type_none;
//	//unsigned char input_direction = direction_type_none;
//	//unsigned char gamer_collision = coll_type_empty;
//	//unsigned char gamer_tile_type = tile_type_blank;
//	//unsigned char oneup_count = 0;
//
//	//unsigned char proceed;
//	//unsigned char input;
//	////unsigned char bossX;
//	//unsigned char check;
//	//unsigned int frame = fo->frame_count;
//	//st->state_object_actor_kill = actor_type_kid;
//
//	//// Draw sprites first.
//	////engine_boss_manager_draw();
//	//engine_gamer_manager_draw();
//
//	//// Set the current screen first.
//	*screen_type = st->state_object_curr_screen;
//
//
//	////engine_frame_manager_draw();
//	////engine_delay_manager_draw();
//	//if( !first_time )
//	//{
//	//	proceed = engine_delay_manager_update();
//	//	if( !proceed )
//	//	{
//	//		return;
//	//	}
//
//	//	engine_frame_manager_update();
//	//	first_time = 1;
//	//}
//
//	//// Continue...
//	//frame = fo->frame_count;
//
//
//	//// Does player want to quit out?
//	//input = engine_input_manager_move( input_type_fire2 );
//	//if( input )
//	//{
//	//	check = engine_reset_manager_update();
//	//	if( check )
//	//	{
//	//		engine_board_manager_midd_text();
//	//		*screen_type = screen_type_over;
//	//		return;
//	//	}
//	//}
//	//else
//	//{
//	//	engine_reset_manager_reset();
//	//}
//
//
//	//// Move gamer.
//	//if( direction_type_none != go->direction && lifecycle_type_move == go->lifecycle )
//	//{
//	//	//  warning 110: conditional flow changed by optimizer: so said EVELYN the modified DOG
//	//	input_direction = engine_input_manager_direction();
//	//	if( direction_type_none != input_direction && gamer_direction != input_direction )
//	//	{
//	//		nextr_direction = gamer_direction;
//	//	}
//
//	//	engine_gamer_manager_update();
//
//	//	// Check boost for next cycle.
//	//	gamer_boost = engine_gamer_manager_input_boost( go->direction );
//	//	if( pace_type_none != gamer_boost )
//	//	{
//	//		//			engine_command_manager_add( frame, command_type_gamer_speed, gamer_boost );
//	//		engine_gamer_manager_pace( gamer_boost );
//	//	}
//	//}
//	//if( direction_type_none != go->direction && lifecycle_type_idle == go->lifecycle )
//	//{
//	//	// Check gamer collision.
//	//	gamer_tile_type = engine_level_manager_get_tile_type( go->tileX, go->tileY, go->direction, offset_type_none );
//	//	if( tile_type_blank != gamer_tile_type )
//	//	{
//	//		// Collide with [death] tree, candy, bonus or one up therefore process tile accordingly...
//	//		gamer_collision = engine_collision_manager_tile_collision( gamer_tile_type );
//	//		if( coll_type_block == gamer_collision )
//	//		{
//	//			engine_gamer_manager_dead();
//	//			st->state_object_actor_kill = actor_type_tree;
//	//		}
//	//	}
//
//	//	engine_gamer_manager_stop();
//	//}
//	//// For continuity we want to check if actor can move immediately after stopping.
//	//if( direction_type_none == go->direction && lifecycle_type_idle == go->lifecycle )
//	//{
//	//	if( coll_type_empty == gamer_collision )
//	//	{
//	//		if( direction_type_none != nextr_direction )
//	//		{
//	//			gamer_direction = nextr_direction;
//	//			nextr_direction = direction_type_none;
//	//		}
//	//		else
//	//		{
//	//			gamer_direction = engine_input_manager_direction();
//	//		}
//
//	//		gamer_direction = engine_gamer_manager_find_direction( gamer_direction );
//	//		if( direction_type_none != gamer_direction )
//	//		{
//	//			//engine_command_manager_add( frame, command_type_gamer_mover, gamer_direction );
//	//			engine_gamer_manager_move( gamer_direction );
//
//	//			gamer_boost = engine_gamer_manager_input_boost( gamer_direction );
//	//			if( pace_type_none != gamer_boost )
//	//			{
//	//				//					engine_command_manager_add( frame, command_type_gamer_speed, gamer_boost );
//	//				engine_gamer_manager_pace( gamer_boost );
//	//			}
//	//		}
//	//	}
//	//}
//
//
//	//// Execute all commands for this frame.
//	////engine_command_manager_execute( frame );
//	//first_time = 0;
//
//
//	//// Check oneup collision before sprite collision as we want to test if all oneup eaten = boss complete.
//	//if( coll_type_oneup == gamer_collision )
//	//{
//	//	oneup_count = engine_score_manager_get_oneup();
//	//	engine_audio_manager_sfx_play( sfx_type_power );
//	//	if( lo->level_object_oneup_count == oneup_count )
//	//	{
//	//		*screen_type = screen_type_pass;
//	//		return;
//	//	}
//	//}
//
//	//// Kid invincible thus don't check for death collisions.
//	//if( st->state_object_localcheat )
//	//{
//	//	return;
//	//}
//
//	//// Kid collide with death tree?
//	//if( st->state_object_trees_type == tree_type_death )
//	//{
//	//	if( actor_type_kid != st->state_object_actor_kill )
//	//	{
//	//		*screen_type = screen_type_dead;
//	//		return;
//	//	}
//	//}
//}
