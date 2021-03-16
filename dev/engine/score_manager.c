#include "score_manager.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "global_manager.h"
#include "hack_manager.h"
#include "locale_manager.h"
#include "level_manager.h"
#include "state_manager.h"
#include "..\object\locale_object.h"
#include "..\devkit\_sms_manager.h"
#include "..\banks\fixedbank.h"

#define TEXTS_Y		22
#define WORLD_Y		22
#define ROUNT_Y		23

// Global variable.
struct_score_object global_score_object;

static unsigned char bonuses[] = { 10, 20, 40, 80, 200 };
static unsigned char boost_X[] = { 100, 100 };
static unsigned char value_y[] = { TEXT3_Y + 1, TEXT2_Y + 1, TEXT4_Y + 1, 22, 23 };
static unsigned char title_Y[] = { TEXT0_Y, TEXT1_Y, TEXT3_Y, TEXT2_Y, TEXT4_Y, };

// TODO need to split the reset functionality.
static void update_score( unsigned char points );
static void update_lives( signed char value );

static void draw_value( unsigned char index );
static void draw_highs();
static void draw_score();
static void draw_zero( unsigned char x, unsigned char y );

void engine_score_manager_text()
{
	const unsigned char *text;
	unsigned char index;

	devkit_SMS_mapROMBank( FIXED_BANK );
	for( index = 0; index < SCORE_VALUES; index++ )
	{
		text = locale_object_texts[ index + 3 ];
		engine_font_manager_draw_text( text, TEXT_X + 1, title_Y[ index ] );
	}
}

void engine_score_manager_init()
{
	struct_score_object *so = &global_score_object;
	struct_state_object *st = &global_state_object;
	so->score = 0;

	so->values[ score_type_lives ] = NUMBER_LIVES - st->state_object_difficulty;
	draw_zero( DATA_X + 1, TEXT0_Y + 1 );
	draw_zero( DATA_X + 1, TEXT1_Y + 1 );
	draw_highs();
	draw_score();
	draw_value( score_type_lives );
}

void engine_score_manager_load()
{
	struct_score_object *so = &global_score_object;
	struct_state_object *st = &global_state_object;
	so->values[ score_type_level ] = st->state_object_world_data * MAX_ROUNDS + st->state_object_round_data + 1;
	so->bonus = 0;
	so->candy = 0;
	so->oneup = 0;
	so->values[ score_type_boost ] = boost_X[ st->state_object_pace_speed ];

	draw_value( score_type_level );
	draw_value( score_type_boost );
}

unsigned char engine_score_manager_get_candy()
{
	struct_score_object *so = &global_score_object;
	return so->candy;
}
unsigned char engine_score_manager_get_oneup()
{
	struct_score_object *so = &global_score_object;
	return so->oneup;
}
unsigned char engine_score_manager_get_bonus( unsigned char index )
{
	return bonuses[ index - 3 ];
}
unsigned char engine_score_manager_get_value( unsigned char index )
{
	struct_score_object *so = &global_score_object;
	return so->values[ index ];
}


void engine_score_manager_finish_bonus()
{
	struct_score_object *so = &global_score_object;
	unsigned char bonus = bonuses[ 4 ];
	update_score( bonus );
}

void engine_score_manager_update_bonus( unsigned char index )
{
	struct_score_object *so = &global_score_object;
	struct_level_object *lo = &global_level_object;

	// The bonus tile enum is 3x values off.
	unsigned char bonus = bonuses[ index - 3 ];
	bonus *= lo->level_object_multiplier;
	so->bonus++;
	update_score( bonus );
}

void engine_score_manager_update_candy()
{
	struct_score_object *so = &global_score_object;
	so->candy++;
	update_score( 1 );
}

void engine_score_manager_update_oneup()
{
	struct_score_object *so = &global_score_object;
	so->oneup++;
	update_score( 2 );
}

void engine_score_manager_update_lives( signed char value )
{
	update_lives( value );
}

void engine_score_manager_update_boost()
{
	struct_score_object *so = &global_score_object;
	struct_state_object *st = &global_state_object;
	struct_hack_object *ho = &global_hack_object;
	if( ho->hack_object_full_boost )
	{
		return;
	}

	if( 0 == so->values[ score_type_boost ] )
	{
		return;
	}

	so->values[ score_type_boost ] -= 1 + st->state_object_difficulty;
	draw_value( score_type_boost );
}



void engine_score_manager_draw_init()
{
		draw_zero( DATA_X + 1, TEXT0_Y + 1 );
		draw_zero( DATA_X + 1, TEXT1_Y + 1 );
		draw_highs();
		draw_score();
		draw_value( score_type_lives );
}
void engine_score_manager_draw_load()
{
		draw_value( score_type_level );
		draw_value( score_type_boost );
}

// Call this function on load level.
void engine_score_manager_update_level()
{
	struct_score_object *so = &global_score_object;
	struct_state_object *st = &global_state_object;
	so->values[ score_type_level ] = st->state_object_world_data * MAX_ROUNDS + st->state_object_round_data + 1;
	draw_value( score_type_level );
	draw_value( score_type_world );
	draw_value( score_type_round );
}

void engine_score_manager_reset_lives()
{
	struct_score_object *so = &global_score_object;
	struct_state_object *st = &global_state_object;

	so->values[ score_type_lives ] = NUMBER_LIVES - st->state_object_difficulty;
	draw_value( score_type_lives );
}
void engine_score_manager_reset_boost()
{
	struct_score_object *so = &global_score_object;
	struct_state_object *st = &global_state_object;

	so->values[ score_type_boost ] = boost_X[ st->state_object_difficulty ];
	draw_value( score_type_boost );
}


static void update_score( unsigned char points )
{
	struct_score_object *so = &global_score_object;
	struct_state_object *st = &global_state_object;
	so->score += points;

	if( so->score > MAX_HI_SCORE )
	{
		so->score = MAX_HI_SCORE;
	}
	if( so->score > st->state_object_high_score )
	{
		st->state_object_high_score = so->score;
		draw_highs();
	}

	draw_score();
}
static void update_lives( signed char value )
{
	struct_score_object *so = &global_score_object;
	if( 0 == so->values[ score_type_lives ] && value < 0 )
	{
		return;
	}
	if( 99 == so->values[ score_type_lives ] && value > 0 )
	{
		return;
	}

	so->values[ score_type_lives ] += value;
	draw_value( score_type_lives );
}

static void draw_highs()
{
	struct_state_object *st = &global_state_object;
	engine_font_manager_draw_data( st->state_object_high_score, DATA_X + 0, TEXT0_Y + 1 );
}
static void draw_score()
{
	struct_score_object *so = &global_score_object;
	engine_font_manager_draw_data( so->score, DATA_X + 0, TEXT1_Y + 1 );
}

static void draw_value( unsigned char index )
{
	struct_score_object *so = &global_score_object;
	struct_state_object *st = &global_state_object;
	unsigned char y_val = value_y[ index ];
	unsigned char value = 0;

	if( index < score_type_world )
	{
		value = so->values[ index ];
	}
	else if( score_type_world == index )
	{
		value = st->state_object_world_data + 1;
	}
	else if( score_type_round == index )
	{
		value = st->state_object_round_data + 1;
	}

	engine_font_manager_draw_data( value, DATA_X + 1, y_val );

	if( value < 10 )
	{
		draw_zero( DATA_X + 0, y_val );
	}
}

static void draw_zero( unsigned char x, unsigned char y )
{
	engine_font_manager_draw_char( '0', x, y );
}