#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

// Music.
void engine_audio_manager_music_play( unsigned char index );
void engine_audio_manager_music_play_norepeat( unsigned char index );
void engine_audio_manager_music_resume();
void engine_audio_manager_music_stop();

// Sound.
void engine_audio_manager_sfx_play( unsigned char index );

#endif//_AUDIO_MANAGER_H_