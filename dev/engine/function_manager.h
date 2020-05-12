#ifndef _FUNCTION_MANAGER_H_
#define _FUNCTION_MANAGER_H_

void engine_function_manager_convertXYtoZ( unsigned char divide, unsigned char x, unsigned char y, unsigned char *z );
void engine_function_manager_convertZtoXY( unsigned char divide, unsigned char z, unsigned char *x, unsigned char *y );

void engine_function_manager_convertByteToNibbles( unsigned char byte, unsigned char *upper_nibble, unsigned char *lower_nibble );
void engine_function_manager_convertNibblesToByte( unsigned char upper_nibble, unsigned char lower_nibble, unsigned char *byte );

#endif//_FUNCTION_MANAGER_H_