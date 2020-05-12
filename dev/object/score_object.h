#ifndef _SCORE_OBJECT_H_
#define _SCORE_OBJECT_H_

#include "..\engine\global_manager.h"

typedef struct tag_struct_score_object
{
	unsigned int score;
	unsigned char values[ SCORE_VALUES ];
	unsigned char bonus;
	unsigned char candy;
	unsigned char oneup;

} struct_score_object;

#endif//_SCORE_OBJECT_H_