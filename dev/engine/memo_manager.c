#include "memo_manager.h"
#include "board_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "locale_manager.h"
#include "score_manager.h"
#include "state_manager.h"
#include "..\object\locale_object.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"

//void engine_memo_manager_clear()
//{
//	unsigned char row;
//	for( row = 0; row < 24; row++ )
//	{
//		engine_font_manager_draw_text( locale_object_blank18, 0, row );
//		engine_font_manager_draw_text( locale_object_blank18, 14, row );
//	}
//}

void engine_memo_manager_draw( unsigned char topIndex, unsigned char botIndex )
{
	unsigned char x = SCREEN_TILE_LEFT + LFT_SIDE_X + 8;
	unsigned char y = TOP_SIDE_Y + 10;

	engine_board_manager_midd_text();
	engine_locale_manager_draw_text( topIndex, x, y + 1 );
	engine_locale_manager_draw_text( botIndex, x, y + 2 );
}

void engine_memo_manager_pass( unsigned char perfect )
{
	unsigned char topIndex = 14;
	unsigned char botIndex = 15;

	if( perfect )
	{
		botIndex = 16;
	}

	engine_memo_manager_draw( topIndex, botIndex );
}

// TODO maybe take out permanently as I won't use...
//void engine_memo_manager_bonus( unsigned char perfect )
//{
//	unsigned char topIndex = 18;
//	unsigned char botIndex = 19;
//
//	if( perfect )
//	{
//		topIndex = 20;
//		botIndex = 21;
//	}
//
//	engine_memo_manager_draw( topIndex, botIndex );
//}

void engine_memo_manager_levels( unsigned char x, unsigned char y1, unsigned char y2 )
{
	struct_state_object *st = &global_state_object;

	engine_font_manager_draw_text( locale_object_number[ st->state_object_world_data ], SCREEN_TILE_LEFT + x, y1 );
	engine_font_manager_draw_text( locale_object_number[ st->state_object_round_data ], SCREEN_TILE_LEFT + x, y2 );
}

void engine_memo_manager_option()
{
	struct_state_object *st = &global_state_object;
	const unsigned char *text;
	unsigned char x = TEXT_X + 2;

	devkit_SMS_mapROMBank( FIXED_BANK );
	if( pace_type_slow == st->state_object_pace_speed )
	{
		text = locale_object_texts[ st->state_object_difficulty + 8 ];
		engine_font_manager_draw_text( text, x, BOTT_TEXT_Y + 1 );
		text = locale_object_texts[ 24 ];
		engine_font_manager_draw_text( text, x, BOTT_TEXT_Y + 2 );
	}
	else
	{
		// TODO do I want to delete this code?
		// extra bytes for ROM hack mode
		if( diff_type_hard == st->state_object_difficulty && pace_type_fast == st->state_object_pace_speed )
		{
			text = locale_object_texts[ st->state_object_difficulty + 8 ];
			engine_font_manager_draw_text( text, x, BOTT_TEXT_Y + 1 );

			text = locale_object_texts[ st->state_object_pace_speed + 10 ];
			engine_font_manager_draw_text( text, x, BOTT_TEXT_Y + 2 );
		}
		else
		{
			text = locale_object_texts[ st->state_object_pace_speed + 10 ];
			engine_font_manager_draw_text( text, x, BOTT_TEXT_Y + 1 );

			text = locale_object_texts[ st->state_object_difficulty + 8 ];
			engine_font_manager_draw_text( text, x, BOTT_TEXT_Y + 2 );
		}
	}
}


void engine_memo_manager_debugging( unsigned char enemy, unsigned char action )
{
	unsigned char x = 26 + enemy * 2 + 1;
	unsigned char y = 21;
	unsigned char text[] = { 'S', 'A', 'W', 'H' };
	engine_font_manager_draw_char( text[ action ], x, y );
}