#include "command_manager.h"
#include "actor_manager.h"
#include "enum_manager.h"
#include "global_manager.h"

#define MAX_FRAMES	255

static void( *execute[ MAX_CMD_TYPE ] )( unsigned char args );
static void( *undo[ MAX_CMD_TYPE ] )( unsigned char args );

static unsigned int command_object_frames[ MAX_FRAMES ];
static unsigned char command_object_cmds[ MAX_FRAMES ];
static unsigned char command_object_args[ MAX_FRAMES ];

static unsigned char command_index;
static unsigned char add_index;
static unsigned char exec_index;
static unsigned char undo_index;
static unsigned char play_index;

static void exec_command_all_empty( unsigned char args );
static void undo_command_all_empty( unsigned char args );
static void exec_command_end_gamer( unsigned char args );
static void undo_command_end_gamer( unsigned char args );

void engine_command_manager_init()
{
	// IMPORTANT execute + undo must be same order!!
	execute[ command_type_all_empty ] = exec_command_all_empty;
	execute[ command_type_gamer_mover ] = engine_actor_manager_exec_gamer_mover;
	execute[ command_type_enemy_mover ] = engine_actor_manager_exec_enemy_mover;
	execute[ command_type_gamer_speed ] = engine_actor_manager_exec_gamer_speed;
	execute[ command_type_enemy_speed ] = engine_actor_manager_exec_enemy_speed;
	execute[ command_type_end_gamer ] = exec_command_end_gamer;

	undo[ command_type_all_empty ] = undo_command_all_empty;
	undo[ command_type_gamer_mover ] = engine_actor_manager_exec_gamer_mover;
	undo[ command_type_enemy_mover ] = engine_actor_manager_exec_enemy_mover;
	undo[ command_type_gamer_speed ] = engine_actor_manager_exec_gamer_speed;
	undo[ command_type_enemy_speed ] = engine_actor_manager_exec_enemy_speed;
	undo[ command_type_end_gamer ] = undo_command_end_gamer;
}

void engine_command_manager_load()
{
	unsigned int index;
	for( index = 0; index < MAX_COMMANDS; index++ )
	{
		command_object_frames[ index ] = 0;
		command_object_cmds[ index ] = 0;
		command_object_args[ index ] = 0;
	}

	command_index = 0;
	add_index = 0;
	exec_index = 0;
	undo_index = 0;
	play_index = 0;
}


void engine_command_manager_add( unsigned int frame, unsigned char command_type, unsigned char args )
{
	command_object_frames[ add_index ] = frame;
	command_object_cmds[ add_index ] = command_type;
	command_object_args[ add_index ] = args;
	add_index++;
}

void engine_command_manager_execute( unsigned int frame )
{
	unsigned int check;
	unsigned char command;
	unsigned int args;

	// If we are not on the correct frame to execute then simply return.
	check = command_object_frames[ exec_index ];
	if( ( frame != check ) || ( add_index == exec_index ) )
	{
		return;
	}

	while( 1 )
	{
		command_index = exec_index;
		command = command_object_cmds[ command_index ];

		args = command_object_args[ command_index ];
		execute[ command ]( args );

		// The index will wrap from 255 to 0 naturally.
		exec_index++;

		// Execute all commands for this frame so break.
		if( add_index == exec_index )
		{
			break;
		}
	}

	// Execute all commands this frame thus increment frame index.
	undo_index = command_index;
}

void engine_command_manager_undo( unsigned int frame )
{
	unsigned int check;
	unsigned char command;
	unsigned int args;

	// If we are not on the correct frame to execute then simply return.
	check = command_object_frames[ undo_index ];
	if( ( frame != check ) )
	{
		return;
	}

	while( 1 )
	{
		command_index = undo_index;
		command = command_object_cmds[ command_index ];

		args = command_object_args[ command_index ];
		undo[ command ]( args );

		// Decrement undo index and break if at the end...
		if( undo_index > 0 )
		{
			undo_index--;
		}
		if( 0 == command_index && 0 == undo_index )
		{
			break;
		}

		check = command_object_frames[ undo_index ];
		if( ( frame != check ) )
		{
			break;
		}
	}
}

void engine_command_manager_play( unsigned int frame )
{
	unsigned int check;
	unsigned char command;
	unsigned int args;

	// If we are not on the correct frame to execute then simply return.
	check = command_object_frames[ play_index ];
	if( ( frame != check ) )
	{
		return;
	}

	while( 1 )
	{
		command = command_object_cmds[ play_index ];
		args = command_object_args[ play_index ];
		execute[ command ]( args );

		// The index will wrap from 255 to 0 naturally.
		play_index++;

		// Execute all commands for this frame so break.
		check = command_object_frames[ play_index ];
		if( ( frame != check ) )
		{
			break;
		}
	}
}

void engine_command_manager_demo( unsigned int* frames, unsigned char* commands, unsigned char* args )
{
	unsigned int index;
	for( index = 0; index < MAX_COMMANDS; index++ )
	{
		command_object_frames[ index ] = frames[ index ];
		command_object_cmds[ index ] = commands[ index ];
		command_object_args[ index ] = args[ index ];
	}
}

static void exec_command_all_empty( unsigned char args )
{
	args = 0;
}
static void undo_command_all_empty( unsigned char args )
{
	args = 0;
}
static void exec_command_end_gamer( unsigned char args )
{
	args = 0;
}
static void undo_command_end_gamer( unsigned char args )
{
	args = 0;
}