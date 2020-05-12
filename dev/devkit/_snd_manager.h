#ifndef _PSG_MANAGER_H_
#define _PSG_MANAGER_H_

void devkit_PSGPlay( void *song );
void devkit_PSGPlayNoRepeat( void *song );
void devkit_PSGStop( void );
void devkit_PSGResume( void );
unsigned char devkit_PSGGetStatus( void );
void devkit_PSGSetMusicVolumeAttenuation( unsigned char attenuation );

void devkit_PSGSFXPlay( void *sfx, unsigned char channels );
void devkit_PSGSFXStop( void );
unsigned char devkit_PSGSFXGetStatus( void );

void devkit_PSGSilenceChannels( void );
void devkit_PSGRestoreVolumes( void );

void devkit_PSGFrame( void );
void devkit_PSGSFXFrame( void );

// #defines
unsigned char devkit_SFX_CHANNEL2();
unsigned char devkit_SFX_CHANNEL3();
unsigned char devkit_SFX_CHANNELS2AND3();

#endif//_PSG_MANAGER_H_