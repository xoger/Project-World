#pragma once
#include "ObjectComponant.h"

class PlayMusic : public ObjectComponant
{
public:
	void init() override;
	void Update(GameObject *Object) override;
	std::string track = " ";
	float volume=1;

private:
	static DerivedRegister<PlayMusic> reg;
	ISound *sound;
};
