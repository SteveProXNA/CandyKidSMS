#ifndef _STORAGE_MANAGER_H_
#define _STORAGE_MANAGER_H_

#include "..\object\storage_object.h"

// Global variable.
extern struct_storage_object global_savegame_object;

unsigned char engine_storage_manager_available();
void engine_storage_manager_read();
void engine_storage_manager_write();
void engine_storage_manager_erase();

#endif//_STORAGE_MANAGER_H_