#ifndef _LEVEL_OBJECT_H_
#define _LEVEL_OBJECT_H_

typedef struct tag_struct_level_object
{
	unsigned char level_object_bonus_count;
	unsigned char level_object_candy_count;
	unsigned char level_object_oneup_count;
	unsigned char level_object_multiplier;

} struct_level_object;

// DATA bank.
// Level Manager.
extern unsigned char level_object_tiles_array[];


// FIXED bank.
// Level Manager.
//extern const unsigned char *level_object_AAdata[];
//extern const unsigned char level_object_AAsize[];
//extern const unsigned char level_object_AAbank[];
//
//extern const unsigned char *level_object_BBdata[];
//extern const unsigned char level_object_BBsize[];
//extern const unsigned char level_object_BBbank[];

#endif//_LEVEL_OBJECT_H_