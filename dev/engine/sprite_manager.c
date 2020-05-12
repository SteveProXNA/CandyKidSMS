#include "sprite_manager.h"
#include "enum_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\bank2.h"

//static void draw_boss( unsigned char x, unsigned char y, unsigned char wide, unsigned char high, unsigned char half, unsigned char hexs );

void engine_sprite_manager_draw_entity( unsigned char x, unsigned char y, unsigned int tile )
{
	devkit_SMS_addSprite( x + 0, y + 0, tile + 0 );
	devkit_SMS_addSprite( x + 8, y + 0, tile + 1 );
	devkit_SMS_addSprite( x + 0, y + 8, tile + 6 );
	devkit_SMS_addSprite( x + 8, y + 8, tile + 7 );
}

void engine_sprite_manager_draw_boss1( unsigned char x, unsigned char y )
{
	unsigned int tile;
	unsigned char row, col;

	for( row = 0; row < TILE_HALF; row++ )
	{
		for( col = 0; col < TILE_HEXS; col++ )
		{
			tile = SPRITE_TILES + row * TILE_HEXS + col;
			devkit_SMS_addSprite( x + col * TILE_HALF, y + row * TILE_HALF, tile );
		}
	}

	//draw_boss( x, y, 0, 0, TILE_HALF, TILE_HEXS );
}

void engine_sprite_manager_draw_boss2( unsigned char wide, unsigned char high, unsigned char x, unsigned char y )
{
	unsigned int tile;
	unsigned char row, col;
	unsigned char top, lft;

	// TL	(t, l) = (0, 0)
	// TR	(t, l) = (0, 3)
	// BL	(t, l) = (4, 0)
	// BR	(t, l) = (4, 3)
	top = high * 4;
	lft = wide * 3;
	for( row = 0; row < TILE_HALF / 2; row++ )
	{
		for( col = 0; col < TILE_HEXS / 2; col++ )
		{
			tile = SPRITE_TILES + ( top + row ) * TILE_HEXS + ( lft + col );
			devkit_SMS_addSprite( x + col * TILE_HALF, y + row * TILE_HALF, tile );
		}
	}

	//draw_boss( x, y, wide, high, 2 );
}

//static void draw_boss( unsigned char x, unsigned char y, unsigned char lft, unsigned char top, unsigned char half, unsigned char hexs )
//{
//	unsigned int tile;
//	unsigned char row, col;
//
//	for( row = 0; row < half; row++ )
//	{
//		for( col = 0; col < hexs; col++ )
//		{
//			tile = SPRITE_TILES + ( top + row ) * TILE_HEXS + ( lft + col );
//			devkit_SMS_addSprite( x + col * TILE_HALF, y + row * TILE_HALF, tile );
//		}
//	}
//}