#include "ObjectCreator.h"
#include <tinyxml2.h>
#include <XMLSerialization.h>
using namespace tinyxml2;
using namespace xmls;
class XMLTree : public Serializable
{
public:
	xFloat scale;
	xString texture;

	XMLTree()
	{
		setClassName("XMLGameObject");
		setVersion("1");

		Register("scale", &scale);
		Register("texture", &texture);
	}
};
class XMLTreeCollection : public Serializable
{
public:
	Collection < XMLTree > XMLTrees;
	XMLTreeCollection()
	{
		setClassName("XMLTreeCollection");
		setVersion("1");
		Register("XMLTrees", &XMLTrees);
	}
};
ObjectCreator::ObjectCreator(ISceneManager *Scnmgr, EventReceiver *Receiver, vector<GameObject> *Objects, irr::gui::ICursorControl *Mous, ISceneCollisionManager *Colmgr, ICameraSceneNode *Camera, IVideoDriver *Driver)
{
	driver = Driver;
	camera = Camera;
	colmgr = Colmgr;
	mous = Mous;
	objects = Objects;
	scnmgr = Scnmgr;
	receiver = Receiver;
	loadtrees();
}
void ObjectCreator::Update()
{
	if (receiver->IsKeyDownOnce(KEY_KEY_T))
		AddTree();
}
void ObjectCreator::loadtrees()
{
	XMLDocument mapfile;
	mapfile.LoadFile("trees.xml");
	XMLPrinter printer;
	mapfile.Print(&printer);
	std::string xml;
	xml = printer.CStr();
	XMLTreeCollection* treecollection = new XMLTreeCollection();
	if (Serializable::fromXML(xml, treecollection))
	{
		for (unsigned int i = 0; i < treecollection->XMLTrees.size(); i++)
		{
			XMLTree *tree = treecollection->XMLTrees.getItem(i);
			treetex.push_back(tree->texture.c_str());
			treescales.push_back(tree->scale.value());
		}
	}
}
void ObjectCreator::AddTree()
{
	vector3df *collpoint = new vector3df(0,0,0);
	float shortest = 100000;
	ITriangleSelector *triangle = 0;
	vector<GameObject>& objref = *objects;
	for (int i = 0; i < objects->size(); i++)
	{
		if (objref[i].node->getType() != ESNT_BILLBOARD)
		{
			if (objref[i].node->getType() == ESNT_MESH)
				triangle = scnmgr->createTriangleSelector(objref[i].meshnode->getMesh(), objref[i].node);
			if (objref[i].isMouseTarget(mous, colmgr, camera, triangle) < shortest)
			{
				collpoint = &objref[i].collpoint;
				shortest = objref[i].isMouseTarget(mous, colmgr, camera, triangle);
			}
		}
	}
	cout << "TREE!" << endl;
	int v2 = rand() % treetex.size();
	objects->push_back(BillboardGameObject(*collpoint + vector3df(0, driver->getTexture(treetex[v2])->getSize().Height/2*0.5f, 0), vector3df(0, 0, 0), scnmgr,
											driver, irr::io::path("NULL"), 
											irr::io::path(treetex[v2]), true, treescales[v2]));
}