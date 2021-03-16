#ifndef _TILE_MANAGER_H_
#define _TILE_MANAGER_H_

void engine_tile_manager_load_tile( unsigned char *tile_type, unsigned char tile_data );
void engine_tile_manager_load_coll( unsigned char *coll_type, unsigned char tile_data );
void engine_tile_manager_draw_tile( unsigned char tile, unsigned char x, unsigned char y, unsigned char mult );

void engine_tile_manager_draw_blank( unsigned char x, unsigned char y );
void engine_tile_manager_draw_candy( unsigned char x, unsigned char y );
void engine_tile_manager_draw_trees( unsigned char type, unsigned char x, unsigned char y );
void engine_tile_manager_draw_bonus( unsigned char type, unsigned char x, unsigned char y, unsigned char multiplier );
void engine_tile_manager_draw_oneup( unsigned char x, unsigned char y );
void engine_tile_manager_draw_cross( unsigned char type, unsigned char x, unsigned char y );
void engine_tile_manager_draw_sides( unsigned char x, unsigned char y );

void engine_tile_manager_main_title( unsigned char x, unsigned char y );
void engine_tile_manager_main_candy( unsigned char x, unsigned char y );
void engine_tile_manager_main_gamer( unsigned char x, unsigned char y );

void engine_tile_manager_funk_trees( unsigned char x, unsigned char y );

#endif//_TILE_MANAGER_H_