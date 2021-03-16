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

#endif//_LEVEL_OBJECT_H_