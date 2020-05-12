#include "enemy_object.h"
#include "..\engine\enum_manager.h"

// DATA bank.
// Enemy Manager.
//extern const unsigned char enemy_object_directions[] =
//{
//	direction_type_rght, direction_type_upxx, direction_type_down, direction_type_left,
//	direction_type_rght, direction_type_down, direction_type_upxx, direction_type_left,
//	direction_type_left, direction_type_upxx, direction_type_down, direction_type_rght,
//	direction_type_left, direction_type_down, direction_type_upxx, direction_type_rght,
//	direction_type_upxx, direction_type_rght, direction_type_left, direction_type_down,
//	direction_type_down, direction_type_rght, direction_type_left, direction_type_upxx,
//	direction_type_upxx, direction_type_left, direction_type_rght, direction_type_down,
//	direction_type_down, direction_type_left, direction_type_rght, direction_type_upxx,
//};

//const unsigned char enemy_object_image[] =
//{
//	0, 2, 4, 12,		// Pro images.
//	14, 16, 24, 26,		// Adi images.
//	28, 36, 38, 40,		// Suz images.
//};
//
//const unsigned char enemy_object_speed[] =
//{
//	//Pro: ES,EF,HS,HF.
//	2, 3, 1, 3, 		// Normal
//	2, 1, 3, 2, 		// Boost!
//	//Adi: ES,EF,HS,HF.
//	1, 1, 2, 3, 		// Normal
//	1, 2, 3, 1, 		// Boost!
//	//Suz: ES,EF,HS,HF.
//	1, 1, 1, 2, 		// Normal
//	1, 1, 2, 3, 		// Boost!
//};
//const unsigned char enemy_object_delay[] =
//{
//	//Pro: ES,EF,HS,HF.
//	3, 3, 1, 2, 		// Normal
//	3, 1, 2, 1, 		// Boost!
//	//Adi: ES,EF,HS,HF.
//	2, 2, 3, 3, 		// Normal
//	2, 3, 3, 1, 		// Boost!
//	//Suz: ES,EF,HS,HF.
//	3, 3, 2, 3, 		// Normal
//	3, 2, 3, 3, 		// Boost!
//};
//
//
//const unsigned char enemy_object_hands[] =
//{
//	//	ES, EF, HS, HF.
//	90, 80, 70, 60,		// Pro
//	95, 85, 75, 65,		// Adi
//	99, 90, 80, 70,		// Suz
//};
//
//const unsigned char enemy_object_waits[] =
//{
//	//	ES, EF, HS, HF.
//	80, 60, 40, 20,		// Pro
//	85, 65, 45, 25,		// Adi
//	90, 70, 50, 30,		// Suz
//};
//const unsigned char enemy_object_tours[] =
//{
//	//	ES, EF, HS, HF.
//	64, 72, 80, 88,		// Pro
//	68, 76, 84, 92,		// Adi
//	72, 80, 88, 96,		// Suz
//};
//const unsigned char enemy_object_kills[] =
//{
//	//	ES, EF, HS, HF.
//	65, 73, 81, 89,		// Pro
//	69, 77, 85, 93,		// Adi
//	73, 81, 89, 97,		// Suz
//};