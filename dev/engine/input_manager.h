#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

// Public method.
void engine_input_manager_update();
unsigned char engine_input_manager_hold( unsigned char data );
unsigned char engine_input_manager_move( unsigned char data );
unsigned char engine_input_manager_direction();

#endif//_INPUT_MANAGER_H_