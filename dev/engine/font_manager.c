#include "font_manager.h"
#include "global_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\bank2.h"
#include "..\gfx.h"

#define TEXT_ROOT	32		// 32 is " " in ASCII.
#define DATA_ROOT	16		// 16 is "0" (48=16+32)
#define UNIT_ROOT	10		// 10 is decimal
#define DATA_LONG	5		// 4 placeholder

void engine_font_manager_draw_char( const unsigned char ch, unsigned char x, unsigned char y )
{
	const unsigned char *pnt = font_tiles__tilemap__bin;
	unsigned char tile = ch - TEXT_ROOT;
	devkit_SMS_setNextTileatXY( x, y );
	devkit_SMS_setTile( *pnt + tile );
}

void engine_font_manager_draw_text( const unsigned char *text, unsigned char x, unsigned char y )
{
	const unsigned char *pnt = font_tiles__tilemap__bin;
	unsigned char idx = 0;

	while( '\0' != text[idx] )
	{
		signed char tile = text[idx] - TEXT_ROOT;
		devkit_SMS_setNextTileatXY( x++, y );
		devkit_SMS_setTile( *pnt + tile );
		idx++;
	}
}

void engine_font_manager_draw_data( unsigned int data, unsigned char x, unsigned char y )
{
	const unsigned char *pnt = font_tiles__tilemap__bin;

	unsigned char idx;
	signed char tile;

	unsigned int quotient = 0;
	unsigned char remainder = 0;

	for( idx = 0; idx < DATA_LONG; ++idx )
	{
		quotient = data / UNIT_ROOT;
		remainder = data % UNIT_ROOT;
		data /= UNIT_ROOT;

		tile = remainder + DATA_ROOT;
		if( 0 == quotient && 0 == remainder && idx > 0 )
		{
			// Replace with space!
			tile = 0;
		}

		devkit_SMS_setNextTileatXY( x--, y );
		devkit_SMS_setTile( *pnt + tile );
	}
}