#ifndef _TIMER_OBJECT_H_
#define _TIMER_OBJECT_H_

// Delay Object.
typedef struct tag_struct_delay_object
{
	unsigned int delay_value;
	unsigned int delay_timer;

} struct_delay_object;


// Frame Object.
typedef struct tag_struct_frame_object
{
	unsigned int frame_count;

} struct_frame_object;


// Reset Object.
typedef struct tag_struct_reset_object
{
	unsigned char reset_value;
	unsigned char reset_timer;

} struct_reset_object;

#endif//_TIMER_OBJECT_H_