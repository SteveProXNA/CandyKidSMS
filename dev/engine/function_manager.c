#include "function_manager.h"
#include "mask_manager.h"
#include "..\devkit\_sms_manager.h"

void engine_function_manager_convertXYtoZ( unsigned char divide, unsigned char x, unsigned char y, unsigned char *z )
{
	*z = y * divide + x;
}
void engine_function_manager_convertZtoXY( unsigned char divide, unsigned char z, unsigned char *x, unsigned char *y )
{
	*x = z % divide;
	*y = z / divide;
}

void engine_function_manager_convertByteToNibbles( unsigned char byte, unsigned char *upper_nibble, unsigned char *lower_nibble )
{
	*upper_nibble = ( byte >> 4 ) & BYTE_NIBBLE_MASK;
	*lower_nibble = byte & BYTE_NIBBLE_MASK;
}
void engine_function_manager_convertNibblesToByte( unsigned char upper_nibble, unsigned char lower_nibble, unsigned char *byte )
{
	*byte = lower_nibble | ( upper_nibble << 4 );
}