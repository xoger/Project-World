#ifndef GameObject_H_INCLUDED
#define GameObject_H_INCLUDED
#include <irrlicht.h>
#include <string>
#include <vector>
#include "ObjectComponant.h"
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace std;
class GameObject
{
public:
	vector3df collpoint;
	IMesh *model;
	std::string modelname;
	std::string texname;
	bool transparent;
	std::string type;
	ISceneNode *node;
	IMeshSceneNode *meshnode;
	IBillboardSceneNode *billnode;

	vector<ObjectComponant*> componants;
	
	void init(vector3df position, vector3df rotation, ISceneManager *scnmgr, IVideoDriver *driver, irr::io::path mesh, irr::io::path texture, bool transparent, float scale);
	void Update();
	void AddComponant(std::string componant);
	float isMouseTarget(irr::gui::ICursorControl *mous, ISceneCollisionManager *colmgr, ICameraSceneNode *camera, ITriangleSelector *triangle);
};
class AnimatedGameObject : public GameObject
{
public:
	AnimatedGameObject(vector3df position, vector3df rotation, ISceneManager *scnmgr, IVideoDriver *driver, irr::io::path mesh, irr::io::path texture, bool transparent, float scale);
};
class StaticGameObject : public GameObject
{
public:
	StaticGameObject(vector3df position, vector3df rotation, ISceneManager *scnmgr, IVideoDriver *driver, irr::io::path mesh, irr::io::path texture, bool transparent, float scale);
};
class TerrainGameObject : public GameObject
{
public:
	TerrainGameObject(vector3df position, vector3df rotation, ISceneManager *scnmgr, IVideoDriver *driver, irr::io::path mesh, irr::io::path texture, bool transparent, float scale);
};
class BillboardGameObject : public GameObject
{
public:
	BillboardGameObject(vector3df position, vector3df rotation, ISceneManager *scnmgr, IVideoDriver *driver, irr::io::path mesh, irr::io::path texture, bool transparent, float scale);
};
#endif