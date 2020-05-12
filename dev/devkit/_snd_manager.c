#include "_snd_manager.h"

#ifdef _CONSOLE
#include "..\..\tmp\PSGlib.h"
#else
#include "..\..\lib\PSGlib.h"
#endif

void devkit_PSGPlay( void *song )
{
	PSGPlay( song );
}
void devkit_PSGPlayNoRepeat( void *song )
{
	PSGPlayNoRepeat( song );
}
void devkit_PSGStop( void )
{
	PSGStop();
}
void devkit_PSGResume( void )
{
	PSGResume();
}
unsigned char devkit_PSGGetStatus( void )
{
	return PSGGetStatus();
}
void devkit_PSGSetMusicVolumeAttenuation( unsigned char attenuation )
{
	PSGSetMusicVolumeAttenuation( attenuation );
}

void devkit_PSGSFXPlay( void *sfx, unsigned char channels )
{
	PSGSFXPlay( sfx, channels );
}
void devkit_PSGSFXStop( void )
{
	PSGSFXStop();
}
unsigned char devkit_PSGSFXGetStatus( void )
{
	return PSGSFXGetStatus();
}

void devkit_PSGSilenceChannels( void )
{
	PSGSilenceChannels();
}
void devkit_PSGRestoreVolumes( void )
{
	PSGRestoreVolumes();
}

void devkit_PSGFrame( void )
{
	PSGFrame();
}
void devkit_PSGSFXFrame( void )
{
	PSGSFXFrame();
}

// #defines
unsigned char devkit_SFX_CHANNEL2()
{
	return SFX_CHANNEL2;
}
unsigned char devkit_SFX_CHANNEL3()
{
	return SFX_CHANNEL3;
}
unsigned char devkit_SFX_CHANNELS2AND3()
{
	return SFX_CHANNELS2AND3;
}