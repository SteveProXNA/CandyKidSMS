#ifndef _ENUM_MANAGER_H_
#define _ENUM_MANAGER_H_

#include "global_manager.h"

typedef enum tag_enum_screen_type
{
	screen_type_none = 0,
	screen_type_splash = 1,
	screen_type_begin = 2,
	screen_type_intro = 3,
	screen_type_title = 4,
	screen_type_start = 5,
	screen_type_init = 6,
	screen_type_load = 7,
	screen_type_ready = 8,
	screen_type_play = 9,
	screen_type_pass = 10,
	screen_type_dead = 11,
	screen_type_cont = 12,
	screen_type_over = 13,
	screen_type_prep = 14,
	screen_type_fight = 15,
	screen_type_boss = 16,
	screen_type_beat = 17,
	screen_type_option = 18,
	screen_type_credit = 19,
	screen_type_test = 20,

} enum_screen_type;

typedef enum tag_enum_diff_type
{
	diff_type_easy = 0,
	diff_type_hard = 1,

} enum_diff_type;

typedef enum tag_enum_pace_type
{
	pace_type_slow = 0,
	pace_type_fast = 1,
	pace_type_none = 2,

} enum_pace_type;

typedef enum tag_enum_input_type
{
	input_type_up    = 0x01,
	input_type_down  = 0x02,
	input_type_left	 = 0x04,
	input_type_right = 0x08,
	input_type_fire1 = 0x10,
	input_type_fire2 = 0x20,

} enum_input_type;

//typedef enum tag_enum_direction_type
//{
//	direction_type_none = 0,
//	direction_type_upxx = 1,
//	direction_type_down = 2,
//	direction_type_left = 3,
//	direction_type_rght = 4,
//
//} enum_direction_type;

typedef enum tag_enum_direction_type
{
	direction_type_none = 0x00,
	direction_type_upxx = 0x01,
	direction_type_down = 0x02,
	direction_type_left = 0x04,
	direction_type_rght = 0x08,

} enum_direction_type;

typedef enum tag_enum_lifecycle_type
{
	lifecycle_type_idle = 0,
	lifecycle_type_move = 1,
	lifecycle_type_dead = 2,

} enum_lifecycle_type;

typedef enum tag_enum_enemymove_type
{
	enemymove_type_tour = 0,		// Scatter,
	enemymove_type_kill = 1,		// Attacks.
	enemymove_type_wait = 2,		// Warm up.
	enemymove_type_home = 3,		// Go home.

} enemymove_type;

typedef enum tag_enum_tile_type
{
	tile_type_blank = 0,
	tile_type_trees = 1,
	tile_type_candy = 2,
	tile_type_bonusA = 3,
	tile_type_bonusB = 4,
	tile_type_bonusC = 5,
	tile_type_bonusD = 6,
	tile_type_oneup = 7,
	tile_type_cross = 8,

} enum_tile_type;

typedef enum tag_enum_coll_type
{
	coll_type_empty = 0,
	coll_type_block = 1,
	coll_type_candy = 2,
	coll_type_oneup = 3,
	coll_type_cross = 4,

} enum_coll_type;

typedef enum tag_enum_tree_type
{
	tree_type_avoid = 0,
	tree_type_death = 1,
	tree_type_funky = 2,

} enum_tree_type;

typedef enum tag_enum_exit_type
{
	exit_type_public = 0,
	exit_type_closed = 1,

} enum_exit_type;

typedef enum tag_enum_actor_type
{
	actor_type_pro = 0,
	actor_type_adi = 1,
	actor_type_suz = 2,
	actor_type_kid = 3,
	actor_type_tree = 4,
	actor_type_boss1 = 5,
	actor_type_boss2 = 6,

} enum_actor_type;

typedef enum tag_enum_command_type
{
	command_type_all_empty = 0,

	command_type_gamer_mover = 1,
	command_type_enemy_mover = 2,
	command_type_gamer_speed = 3,
	command_type_enemy_speed = 4,

	command_type_end_gamer = MAX_CMD_TYPE - 1,

} enum_command_type;

typedef enum tag_enum_cross_type
{
	cross_type_open = 0,
	cross_type_full = 1,

} enum_cross_type;

typedef enum tag_enum_frame_type
{
	frame_type_stance = 0,
	frame_type_toggle = 1,

} enum_frame_type;

typedef enum tag_enum_score_type
{
	score_type_lives = 0,
	score_type_level = 1,
	score_type_boost = 2,
	score_type_world = 3,
	score_type_round = 4,

} enum_score_type;

typedef enum tag_enum_offset_type
{
	offset_type_none = 0,
	offset_type_one = 1,
	offset_type_two = 2,
	offset_type_four = 4,

} enum_offset_type;

//typedef enum tag_enum_play_type
//{
//	play_type_discrete = 0,
//	play_type_continuous = 1,
//
//} enum_play_type;

typedef enum tag_enum_sfx_type
{
	sfx_type_accept = 0,
	sfx_type_reset = 1,
	sfx_type_power = 2,
	sfx_type_death01 = 3,
	sfx_type_death02 = 4,
	sfx_type_death03 = 5,
	sfx_type_over = 5,

} enum_sfx_type;

typedef enum tag_enum_music_type
{
	mus_type_level = 0,
	mus_type_cont = 1,
	mus_type_over = 2,
	mus_type_game01 = 3,
	mus_type_game02 = 4,
	mus_type_game03 = 5,
	mus_type_beat = 6,
	mus_type_candykid = 7,
	mus_type_boss01 = 8,
	mus_type_boss02 = 9,
	mus_type_boss03 = 10,

} enum_music_type;

typedef enum tag_enum_stage_type
{
	event_stage_start = 0,
	event_stage_pause = 1,

} enum_stage_type;

typedef enum tag_enum_border_type
{
	border_type_game = 0,
	border_type_main = 1,

} enum_border_type;

typedef enum tag_enum_menu_type
{
	menu_type_single = 0,
	menu_type_double = 1,

} enum_menu_type;

typedef enum tag_enum_cursor_type
{
	cursor_type_arrows = 0,
	cursor_type_spaces = 1,

} enum_cursor_type;

typedef enum tag_enum_fight_type
{
	fight_type_enemy = 0,
	fight_type_boss1 = 1,
	fight_type_boss2 = 2,

} enum_fight_type;

typedef enum tag_enum_boss_type
{
	boss_type_large = 0,
	boss_type_small = 1,

} enum_boss_type;

#endif//_ENUM_MANAGER_H_