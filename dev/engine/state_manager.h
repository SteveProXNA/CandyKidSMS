#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include "..\object\state_object.h"

// Global variable.
extern struct_state_object global_state_object;

void engine_state_manager_init();
void engine_state_manager_fight( unsigned char fight );
//void engine_state_manager_level();

#endif//_STATE_MANAGER_H_
