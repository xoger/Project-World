#ifndef EventReceiver_H_INCLUDED
#define EventReceiver_H_INCLUDED
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace std;
class EventReceiver : public IEventReceiver
{
public:
	struct SMouseState
	{
		bool RightButtonDown;
		bool LeftButtonDown;
		bool LeftButtonDownOnce;
		bool RightButtonDownOnce;
	} MouseState, oldMouseState;
	virtual bool OnEvent(const SEvent& event);
	void Update();
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	virtual bool IsKeyDownOnce(EKEY_CODE keyCode) ;
	EventReceiver();
private:
	//store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool OldKeyIsDown[KEY_KEY_CODES_COUNT];
};
#endif