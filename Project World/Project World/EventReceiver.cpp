#include "EventReceiver.h"

bool EventReceiver::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
		case EMIE_RMOUSE_PRESSED_DOWN:
			MouseState.RightButtonDown = true;
			break;
		case EMIE_RMOUSE_LEFT_UP:
			MouseState.RightButtonDown = false;

			break;
		case EMIE_LMOUSE_PRESSED_DOWN:
			MouseState.LeftButtonDown = true;
			break;
		case EMIE_LMOUSE_LEFT_UP:
			MouseState.LeftButtonDown = false;
			break;
		default:
			break;
		}
	}
	return false;
}
void EventReceiver::Update()
{
	if (oldMouseState.LeftButtonDown == false && MouseState.LeftButtonDown == true)
		MouseState.LeftButtonDownOnce = true;
	else
		MouseState.LeftButtonDownOnce = false;

	if (oldMouseState.RightButtonDown == false && MouseState.RightButtonDown == true)
		MouseState.RightButtonDownOnce = true;
	else
		MouseState.RightButtonDownOnce = false;
	oldMouseState = MouseState;
	
}
	//check whether a key is being held down
bool EventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}
bool EventReceiver::IsKeyDownOnce(EKEY_CODE keyCode) 
{
	bool r;
	if (OldKeyIsDown[keyCode] == false)
		r = KeyIsDown[keyCode];
	else r = false;
	for (int i = 0; i < _countof(KeyIsDown); i++)
		OldKeyIsDown[i] = KeyIsDown[i];
	return r;
}

EventReceiver::EventReceiver()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}


