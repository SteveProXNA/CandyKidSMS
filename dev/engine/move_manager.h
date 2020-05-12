#ifndef _MOVE_MANAGER_H_
#define _MOVE_MANAGER_H_

void engine_move_manager_get_directions( unsigned char srceX, unsigned char srceY, unsigned char destX, unsigned char destY, unsigned char *list, unsigned char *half );

unsigned char engine_move_manager_what_direction( unsigned char sourceX, unsigned char sourceY, unsigned char prev_move, unsigned char targetX, unsigned char targetY );
unsigned char engine_move_manager_gothru_exit( unsigned char tileX, unsigned char tileY, unsigned char direction );
unsigned char engine_move_manager_border_exit( unsigned char tileX, unsigned char tileY, unsigned char direction );
unsigned char engine_move_manager_inside_exit( unsigned char tileX, unsigned char tileY );
unsigned char engine_move_manager_opposite_direction( unsigned char direction );

#endif//_MOVE_MANAGER_H_
