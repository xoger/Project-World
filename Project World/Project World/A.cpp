#include "GameObject.h"
#include <Globals.h>
ComponantFactory::map_type* ComponantFactory::map = new map_type();
ISoundEngine* Globals::soundengine = soundengine = createIrrKlangDevice();
