//=================================
// include guard
#ifndef __MODULEAUDIO_H__
#define __MODULEAUDIO_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "DList.h"
#include "SDL_mixer\include\SDL_mixer.h"
//=================================
// macros
#define DEFAULT_MUSIC_FADE_TIME 2.0f
//=================================
// the actual class

class ModuleAudio : public Module
{
private:

	Mix_Music *music;
	DList<Mix_Chunk*> fx;

public:

	ModuleAudio(Application *app, bool start_enabled = true);
	~ModuleAudio();

	bool init();
	bool cleanUp();

	// Play a music file
	bool playMusic(const char *path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int loadFx(const char *path);

	// Play a previously loaded WAV
	bool playFx(unsigned int fx, int repeat = 0);

	// Stop all music
	bool stopAllMusic(float fade_time);
};

#endif //!__MODULEAUDIO_H__