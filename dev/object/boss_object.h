#ifndef _BOSS_OBJECT_H_
#define _BOSS_OBJECT_H_

#include "..\engine\global_manager.h"

typedef struct tag_struct_boss_object
{
	unsigned char actor;
	unsigned char posnX;		// PositionX during movement.
	unsigned char posnY;		// PositionY during movement.
	unsigned char homeX;		// Posn tileX on bossX homes.
	unsigned char homeY;		// Posn tileY on bossX homes.
	unsigned char tileX;		// Posn tileX on bossX stops.
	unsigned char tileY;		// Posn tileY on bossX stops.
	unsigned char tileZ;		// Posn tile stored as R x C.
	unsigned char waiter;		// Wait time when level load.
	unsigned char action;		// Current action: W / T / K.
	unsigned char scatter[ NUM_DIRECTIONS * 2 ];
	unsigned char paths;		// Track enemy scatter paths.
	//unsigned char speeds[ 2 ];
	//unsigned char delays[ 2 ];
	unsigned char speed;
	unsigned char delay;
	unsigned char timer;
	//unsigned char delta;
	unsigned char total;
	unsigned char sizer;		// Size this bossX can shows.
	unsigned char mover;		// Flag when bossX can moves.
	unsigned char drawr;		// Flag when bossX can draws.
	unsigned char wide;			// Used to render small boss.
	unsigned char high;			// Used to render small boss.
	
	unsigned char lifecycle;
	//unsigned char prev_moves[ 4 ];	// Previous direction moved.
	unsigned char prev_move;	// Previous direction moved.
	unsigned char direction;	// Current  direction moved.
	unsigned char image;

} struct_boss_object;


// FIXED bank.
// Boss Manager.
//extern const unsigned char *boss_object_tiles[];
//extern const unsigned char *boss_object_color[];
//extern const unsigned char boss_object_bank[];

//TODO delete
//extern const unsigned char boss_object_tileX[];
//extern const unsigned char boss_object_tileY[];
//TODO delete

#endif//_GAMER_OBJECT_H_