#ifndef ObjectCreator_H_INCLUDED
#define ObjectCreator_H_INCLUDED
#include <irrlicht.h>
#include "EventReceiver.h"
#include <GameObject.h>
#include <vector>
#include <iostream>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace std;
class ObjectCreator
{
public:
	ISceneManager *scnmgr;
	EventReceiver *receiver;
	vector<GameObject> *objects;
	irr::gui::ICursorControl *mous;
	ISceneCollisionManager *colmgr;
	ICameraSceneNode *camera;
	IVideoDriver *driver;
	vector<io::path> treetex;
	vector<float> treescales;
	ObjectCreator(ISceneManager *Scnmgr, EventReceiver *Receiver, vector<GameObject> *Objects, irr::gui::ICursorControl *Mous, ISceneCollisionManager *Colmgr, ICameraSceneNode *Camera, IVideoDriver *Driver);
	void Update();
	void loadtrees();
	void AddTree();
};
#endif