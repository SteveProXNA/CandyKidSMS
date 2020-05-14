#include "audio_object.h"
#include "..\banks\bank6.h"
#include "..\banks\bank7.h"
#include "..\banks\bank8.h"
#include "..\banks\bank9.h"
#include "..\banks\bank10.h"
#include "..\banks\bank11.h"
#include "..\banks\bank12.h"
#include "..\banks\bank13.h"
#include "..\psg.h"

// DATA bank.
// Audio Manager.
const unsigned char *sfx_object_data[] =
{
	sfx_accept_psg,
	sfx_reset_psg,
	sfx_power_psg,
	sfx_death01_psg,
	sfx_death02_psg,
	sfx_death03_psg,
	sfx_over_psg,
};