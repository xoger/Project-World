#include "PlayMusic.h"

DerivedRegister<PlayMusic> PlayMusic::reg("PlayMusic");
void PlayMusic::init()
{
	Identifier = "PlayMusic";
	RegisterVar(&track);
	RegisterVar(&volume);

	sound = Globals::soundengine->play2D(track.c_str(), true, false);
	sound->setVolume(volume);
}
void PlayMusic::Update(GameObject *Object)
{
	
	
}