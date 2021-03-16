#include "board_object.h"
#include "..\engine\enum_manager.h"
#include "..\engine\global_manager.h"

// DATA bank.
// Board Manager.
const unsigned char board_object_posnX[] =
{
	0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0,

};
const unsigned char board_object_posnY[] =
{
	0xF0, 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0,
};

// Order:									  Pro,  Adi,  Suz,  Kid.
const unsigned char board_object_homeX[] = { 0x0A, 0x03, 0x0A, 0x03 };
const unsigned char board_object_homeY[] = { 0x0A, 0x0A, 0x03, 0x03 };

// FIXED bank
// Board Manager.
const unsigned char board_object_wide[] = { TREE_COLS, SCREEN_TILE_WIDE - 1 };
const unsigned char board_object_rght[] = { 22, 28 };
const unsigned char board_object_left[] = { 3, 4 };
const unsigned char board_object_midd[] = { 8, 10 };

// Main
const unsigned char board_object_exitX[] = { 8, 20, 8, 20, 0, 0, 28, 28};
const unsigned char board_object_exitY[] = { 0, 0, 22, 22, 6, 16, 6, 16 };