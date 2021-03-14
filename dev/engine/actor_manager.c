#include "actor_manager.h"
#include "enemy_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "function_manager.h"
#include "gamer_manager.h"

// Execute commands.
//void engine_actor_manager_exec_gamer_mover( unsigned char args )
//{
//	engine_gamer_manager_move( args );
//}
//void engine_actor_manager_exec_enemy_mover( unsigned char args )
//{
//	unsigned char direction;
//	unsigned char enemy;
//
//	engine_function_manager_convertByteToNibbles( args, &direction, &enemy );
//	engine_enemy_manager_move( enemy, direction );
//}
//void engine_actor_manager_exec_gamer_speed( unsigned char args )
//{
//	engine_gamer_manager_pace( args );
//}
//void engine_actor_manager_exec_enemy_speed( unsigned char args )
//{
//	unsigned char boost;
//	unsigned char enemy;
//
//	engine_function_manager_convertByteToNibbles( args, &boost, &enemy );
//	engine_enemy_manager_pace( enemy, boost );
//}


//void engine_actor_manager_get_data( unsigned char *mover, unsigned char *tileZ )
//{
//	struct_gamer_object *go = &global_gamer_object;
//	struct_enemy_object *eo;
//	unsigned char enemy;
//	unsigned char index;
//
//	mover[ 0 ] = 1;
//	tileZ[ 0 ] = go->tileZ;
//	for( enemy = 0; enemy < MAX_ENEMIES; enemy++ )
//	{
//		eo = &global_enemy_objects[ enemy ];
//		index = enemy + 1;
//		mover[ index ] = eo->mover;
//		tileZ[ index ] = eo->tileZ;
//	}
//}