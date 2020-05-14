#include "content_manager.h"
#include "global_manager.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\bank2.h"
#include "..\gfx.h"

#define FONT_TILES		0
#define LOAD_TILES		64
#define SPLASH_TILES	128
#define SCREEN_TILES	224

// Tiles.
void engine_content_manager_load_tiles_font()
{
	// Font tiles.
	devkit_SMS_loadPSGaidencompressedTiles( font_tiles__tiles__psgcompr, FONT_TILES );
	devkit_SMS_loadBGPalette( ( void * ) font_tiles__palette__bin );
}

void engine_content_manager_load_tiles_game()
{
	// Game tiles.
	devkit_SMS_loadPSGaidencompressedTiles( game_tiles__tiles__psgcompr, LOAD_TILES );
	devkit_SMS_loadBGPalette( ( void * ) game_tiles__palette__bin );
}

void engine_content_manager_load_tiles_main()
{
	// Main tiles.
	devkit_SMS_mapROMBank( main_tiles__tiles__psgcompr_bank );
	devkit_SMS_loadPSGaidencompressedTiles( main_tiles__tiles__psgcompr, LOAD_TILES );
	devkit_SMS_loadBGPalette( ( void * ) main_tiles__palette__bin );
}

void engine_content_manager_load_tiles_splash()
{
	devkit_SMS_mapROMBank( splash__tiles__psgcompr_bank );
	devkit_SMS_loadPSGaidencompressedTiles( splash__tiles__psgcompr, SPLASH_TILES );
	devkit_SMS_loadSTMcompressedTileMap( 0, 0, ( void * ) splash__tilemap__stmcompr );
	devkit_SMS_loadBGPalette( ( void * ) splash__palette__bin );
}


// Sprites.
void engine_content_manager_load_sprites_game()
{
	// Sprite tiles.
	devkit_SMS_loadPSGaidencompressedTiles( sprites__tiles__psgcompr, SPRITE_TILES + 48 );
	devkit_SMS_loadSpritePalette( ( void * ) sprites__palette__bin );
}