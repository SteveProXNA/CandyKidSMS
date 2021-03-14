//#include "test_screen.h"
//#include "..\engine\asm_manager.h"
//#include "..\engine\audio_manager.h"
//#include "..\engine\board_manager.h"
//#include "..\engine\boss_manager.h"
//#include "..\engine\content_manager.h"
//#include "..\engine\enemy_manager.h"
//#include "..\engine\enum_manager.h"
//#include "..\engine\font_manager.h"
//#include "..\engine\gamer_manager.h"
//#include "..\engine\global_manager.h"
//#include "..\engine\input_manager.h"
//#include "..\engine\level_manager.h"
//#include "..\engine\locale_manager.h"
//#include "..\engine\main_manager.h"
//#include "..\engine\memo_manager.h"
//#include "..\engine\option_manager.h"
//#include "..\engine\score_manager.h"
//#include "..\engine\sprite_manager.h"
//#include "..\engine\tile_manager.h"
//#include "..\devkit\_sms_manager.h"
//#include "..\object\level_object.h"
//#include "..\banks\bank11.h"
//
////static void load_boss32();
//////static void draw_boss32();
////
////static void draw_boss32( unsigned char index, unsigned char x, unsigned char y );
////static void draw_boss64( unsigned char x, unsigned char y );
////static void draw_oneup( unsigned char col, unsigned char row );
//
//void screen_test_screen_load()
//{
//	devkit_SMS_displayOff();
//	engine_asm_manager_clear_VRAM();
//	engine_content_manager_load_tiles_font();
//	engine_content_manager_load_tiles_main();
//	engine_content_manager_load_sprites_game();
//	devkit_SMS_displayOn();
//
//	engine_score_manager_load();
//	engine_gamer_manager_reset();
//	engine_gamer_manager_load();
//
//	engine_boss_manager_setup( 1 );
//	engine_boss_manager_load();
//}
//
//void screen_test_screen_update( unsigned char *screen_type )
//{
//	//engine_gamer_manager_draw();
//	//engine_enemy_manager_draw();
//
//	// top left		3, 3
//	//draw_boss64( 48-16, 32-16 );
//
//	//// bot left		3, 9
//	//draw_boss64( 48 - 16, 144 - 32 );
//	//draw_boss64( 48 - 16, 128 - 16 );
//
//	//// top right	10, 3
//	//draw_boss64( 160 - 16, 32 - 16 );
//
//	//// bot right	10, 9
//	//draw_boss64( 160 - 16, 128 - 16 );
//
//	//draw_boss32( 1, 48 - 16, 144 - 16 );
//	//draw_boss32( 2, 160 - 16, 32 - 16 );
//	*screen_type = screen_type_test;
//}
//
////static void load_boss32()
////{
////	devkit_SMS_mapROMBank( boss32_00__tiles__psgcompr_bank );
////	devkit_SMS_loadPSGaidencompressedTiles( boss32_00__tiles__psgcompr, SPRITE_TILES );
////	devkit_SMS_loadSpritePalette( ( void * ) boss32_00__palette__bin );
////}
//////static void load_boss64()
//////{
//////	devkit_SMS_mapROMBank( boss64_00__tiles__psgcompr_bank );
//////	devkit_SMS_loadPSGaidencompressedTiles( boss64_00__tiles__psgcompr, SPRITE_TILES );
//////	devkit_SMS_loadSpritePalette( ( void * ) boss64_00__palette__bin );
//////}
////
////static void draw_boss32( unsigned char index, unsigned char x, unsigned char y )
////{
////	//engine_sprite_manager_draw_boss1
////	//unsigned int tile;
////	//unsigned char r, c;
////	//unsigned char t, l;
////
////	//// TL	(t, l) = (0, 0)
////	//// TR	(t, l) = (0, 3)
////	//// BL	(t, l) = (4, 0)
////	//// BR	(t, l) = (4, 3)
////	//t = boss_object_tileX[ index ];
////	//l = boss_object_tileY[ index ];
////	//for( r = 0; r < 4; r++ )
////	//{
////	//	for( c = 0; c < 3; c++ )
////	//	{
////	//		tile = SPRITE_TILES + ( t + r ) * 6 + ( l + c );
////	//		devkit_SMS_addSprite( x + c * 8, y + r * 8, tile );
////	//	}
////	//}
////}
////
////static void draw_boss64( unsigned char x, unsigned char y )
////{
////	//unsigned int tile;
////	//unsigned char r, c;
////	//for( r = 0; r < 8; r++ )
////	//{
////	//	for( c = 0; c < 6; c++ )
////	//	{
////	//		tile = SPRITE_TILES + r * 6 + c;
////	//		devkit_SMS_addSprite( x + c * 8, y + r * 8, tile );
////	//	}
////	//}
////}
////
////static void draw_oneup( unsigned char col, unsigned char row )
////{
////	unsigned char x = ( col + 1 ) * 2;
////	unsigned char y = ( row + 1 ) * 2;
////	engine_tile_manager_draw_oneup( SCREEN_TILE_LEFT + x, y );
////}