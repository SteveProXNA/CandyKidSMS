#ifndef _GAMER_OBJECT_H_
#define _GAMER_OBJECT_H_

#include "..\engine\global_manager.h"

typedef struct tag_struct_gamer_object
{
	// TODO test for this.
	unsigned char posnX;		// PositionX during movement.
	unsigned char posnY;		// PositionY during movement.
	unsigned char tileX;		// Posn tileX on gamer stops. 
	unsigned char tileY;		// Posn tileY on gamer stops.
	unsigned char tileZ;		// Posn tile stored as R x C.
	unsigned char curr_boost;
	unsigned char prev_boost;
	//unsigned char boost;
	unsigned char speeds[ 2 ];
	unsigned char delays[ 2 ];
	unsigned char speed;
	unsigned char delay;
	unsigned char timer;
	unsigned char delta;
	unsigned char total;
	unsigned char prev_move;	// Previous direction moved.
	unsigned char direction;	// Current  direction moved.
	unsigned char lifecycle;
	unsigned char image;
	unsigned char frame;
	unsigned int calcd;
	// Allow extra image for death.
	unsigned char images[ NUM_ENTITY_IMAGE + 1 ][ NUM_ENTITY_FRAME ];

} struct_gamer_object;


// FIXED bank.
// Gamer Manager.
//extern const unsigned char gamer_object_image[];
//extern const unsigned char gamer_object_speed[];
//extern const unsigned char gamer_object_delay[];

#endif//_GAMER_OBJECT_H_