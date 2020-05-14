#ifndef _COMMAND_MANAGER_H_
#define _COMMAND_MANAGER_H_

// Public methods.
void engine_command_manager_init();
void engine_command_manager_load();
void engine_command_manager_add( unsigned int frame, unsigned char command_type, unsigned char args );

void engine_command_manager_execute( unsigned int frame );
void engine_command_manager_undo( unsigned int frame );
void engine_command_manager_play( unsigned int frame );

void engine_command_manager_demo( unsigned int* frames, unsigned char* commands, unsigned char* args );

#endif//_COMMAND_MANAGER_H_