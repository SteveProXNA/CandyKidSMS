#ifndef _SCORE_MANAGER_H_
#define _SCORE_MANAGER_H_

#include "..\object\score_object.h"

// Global variable.
extern struct_score_object global_score_object;

void engine_score_manager_text();
void engine_score_manager_init();
void engine_score_manager_load();

unsigned char engine_score_manager_get_candy();
unsigned char engine_score_manager_get_oneup();
unsigned char engine_score_manager_get_bonus( unsigned char index );
unsigned char engine_score_manager_get_value( unsigned char index );
//unsigned char engine_score_manager_get_lives();
//unsigned char engine_score_manager_get_boost();

void engine_score_manager_finish_bonus();
void engine_score_manager_update_bonus( unsigned char bonus );
void engine_score_manager_update_candy();
void engine_score_manager_update_oneup();
void engine_score_manager_update_lives( signed char value );
void engine_score_manager_update_boost();
// TODO delete this - used for debugging!
void engine_score_manager_update_level();

void engine_score_manager_reset_lives();
void engine_score_manager_reset_boost();

#endif//_SCORE_MANAGER_H_
