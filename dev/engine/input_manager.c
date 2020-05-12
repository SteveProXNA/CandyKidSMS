#include "input_manager.h"
#include "enum_manager.h"
#include "..\devkit\_sms_manager.h"

// Must be static to persist values!
static unsigned int curr_joypad1 = 0;
static unsigned int prev_joypad1 = 0;

// Public method.
void engine_input_manager_update()
{
	prev_joypad1 = curr_joypad1;
	curr_joypad1 = devkit_SMS_getKeysStatus();
}

// Public methods HOLD.
unsigned char engine_input_manager_hold( unsigned char data )
{
	return curr_joypad1 & data && !( prev_joypad1 & data );
}

unsigned char engine_input_manager_move( unsigned char data )
{
	return curr_joypad1 & data;
}

unsigned char engine_input_manager_direction()
{
	unsigned char direction = direction_type_none;
	unsigned char upxx;
	unsigned char down;
	unsigned char left;
	unsigned char rght;

	upxx = engine_input_manager_move( input_type_up );
	down = engine_input_manager_move( input_type_down );
	left = engine_input_manager_move( input_type_left );
	rght = engine_input_manager_move( input_type_right );

	// Ignore multi-movement e.g. up-left / down-left / up-right / down-right.
	if( ( upxx && left ) || ( down && left ) || ( upxx && rght ) || ( down && rght ) )
	{
		return direction;
	}
	else
	{
		if( upxx )
		{
			direction = direction_type_upxx;
		}
		else
		{
			if( down )
			{
				direction = direction_type_down;
			}
			else
			{
				if( left )
				{
					direction = direction_type_left;
				}
				else
				{
					if( rght )
					{
						direction = direction_type_rght;
					}
				}
			}
		}
	}

	return direction;
}