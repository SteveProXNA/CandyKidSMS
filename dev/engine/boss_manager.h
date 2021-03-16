#ifndef _BOSS_MANAGER_H_
#define _BOSS_MANAGER_H_

#include "global_manager.h"
#include "..\object\boss_object.h"

// Global variables.
extern struct_boss_object global_boss_objects[ MAX_BOSSES ];

void engine_boss_manager_init();
void engine_boss_manager_setup( unsigned char round );
void engine_boss_manager_load();
void engine_boss_manager_update( unsigned char bossX );
void engine_boss_manager_draw();
void engine_boss_manager_hide();
void engine_boss_manager_move( unsigned char bossX, unsigned char direction );
void engine_boss_manager_stop( unsigned char bossX );
void engine_boss_manager_dead( unsigned char bossX );
void engine_boss_manager_reset_home();
unsigned char engine_boss_manager_scatter_direction( unsigned char bossX );
unsigned char engine_boss_manager_gohome_direction( unsigned char bossX );
void engine_boss_manager_content();
unsigned char engine_boss_manager_index();

#endif//_BOSS_MANAGER_H_
