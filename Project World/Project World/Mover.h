#ifndef Mover_H_INCLUDED
#define Mover_H_INCLUDED
#include <irrlicht.h>
#include "GameObject.h"
#include "EventReceiver.h"
using namespace irr;
using namespace scene;
using namespace video;
using namespace core;
class Mover
{
public:
	vector3df pos;
	Mover(ISceneManager *Scnmgr, IVideoDriver *Driver, irr::gui::ICursorControl *Mous, EventReceiver* Receiver);
	void Update(ICameraSceneNode *camera);
	bool SelectArrow(irr::gui::ICursorControl *mous, ISceneCollisionManager *colmgr, ICameraSceneNode *camera);
	void ChangeObject(ISceneNode *node);
	void Draw();
private:
	bool draw;
	IMeshSceneNode *XYZ[3];
	ISceneNode *object;
	ISceneManager *scnmgr;
	IVideoDriver *driver;
	ITriangleSelector *triangle = 0;
	vector3df directions[3];
	ISceneNode* selected;
	irr::gui::ICursorControl *mous;
	irr::io::path colour[3];
	EventReceiver* receiver;
};
#endif
