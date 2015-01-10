#ifndef MapLoader_H_INCLUDED
#define MapLoader_H_INCLUDED
#include <irrlicht.h>
#include <GameObject.h>
#include <vector>
using namespace std;
class MapLoader
{
public:
	vector<GameObject> Start(irr::scene::ISceneManager *scnmgr, irr::video::IVideoDriver *driver);
	void Save(vector<GameObject> *objects);
};
#endif