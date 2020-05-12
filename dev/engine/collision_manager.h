#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

void engine_collision_manager_load();
unsigned char engine_collision_manager_enemy_collision();
unsigned char engine_collision_manager_boss_collision();
unsigned char engine_collision_manager_tile_collision( unsigned char tile_type );
void engine_collision_manager_reset_death();

#endif//_COLLISION_MANAGER_H_
