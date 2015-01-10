#include <MapLoader.h>
#include <tinyxml2.h>
#include <XMLSerialization.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace tinyxml2;
using namespace xmls;

class XMLGameObject : public Serializable
{
public:
	xFloat posx;
	xFloat posy;
	xFloat posz;
	xFloat rotx;
	xFloat roty;
	xFloat rotz;
	xString model;
	xString texture;
	xBool transparent;
	xFloat scale;
	xString type;
	Collection < XMLObjectComponant > Componants;
	XMLGameObject()
	{
		setClassName("XMLGameObject");
		setVersion("2");

		Register("posx", &posx);
		Register("posy", &posy);
		Register("posz", &posz);
		Register("rotx", &rotx);
		Register("roty", &roty);
		Register("rotz", &rotz);
		Register("model", &model);
		Register("texture", &texture);
		Register("transparent", &transparent);
		Register("scale", &scale);
		Register("type", &type);
		Register("Conponants", &Componants);
	}
};
class XMLGameObjectCollection : public Serializable
{
public:
	Collection < XMLGameObject > XMLGameObjects;
	
	XMLGameObjectCollection()
	{
		setClassName("XMLGameObjectCollection");
		setVersion("1");

		Register("XMLGameObjects", &XMLGameObjects);
		
	}

};
void MapLoader::Save(vector<GameObject> *objects)
{
	XMLGameObjectCollection *Objects = new XMLGameObjectCollection;

	vector <XMLGameObject*> items;
	vector<GameObject>& objref = *objects;
	for (int i = 0; i < objref.size(); i++)
	{
		items.push_back(new XMLGameObject());
		items[i]->posx = objref[i].node->getPosition().X;
		items[i]->posy = objref[i].node->getPosition().Y;
		items[i]->posz = objref[i].node->getPosition().Z;
		
		items[i]->rotx = objref[i].node->getRotation().X;
		items[i]->roty = objref[i].node->getRotation().Y;
		items[i]->rotz = objref[i].node->getRotation().Z;
		items[i]->model = objref[i].modelname;
		
		items[i]->texture = objref[i].texname;
		items[i]->transparent = objref[i].transparent;
		items[i]->scale = objref[i].node->getScale().X;
		items[i]->type = objref[i].type;
		for (int j = 0; j < objref[i].componants.size(); j++)
		{
			
			objref[i].componants[j]->updateXMLvars();
			
			items[i]->Componants.addItem(objref[i].componants[j]->XML);
		}
		Objects->XMLGameObjects.addItem(items[i]);
	}
	
	
	std::string xmlData = Objects->toXML();
	XMLDocument doc;
	doc.Parse(xmlData.c_str());
	doc.SaveFile("XMLGameObjects.xml");
	items.clear();
}
vector<GameObject> MapLoader::Start(irr::scene::ISceneManager *scnmgr, irr::video::IVideoDriver *driver)
{
	static ComponantFactory factory;

	XMLDocument mapfile;

	mapfile.LoadFile("XMLGameObjects.xml");

	XMLPrinter printer;
	mapfile.Print(&printer);
	std::string xml;
	xml = printer.CStr();
	vector<GameObject> map = vector<GameObject>();
	XMLGameObjectCollection *collection = new XMLGameObjectCollection(); // Create new object
	if (Serializable::fromXML(xml, collection)) // perform deserialization
	{
		
		
		for (unsigned int i = 0; i < collection->XMLGameObjects.size(); i++)
		{
			XMLGameObject *stats = collection->XMLGameObjects.getItem(i);
			if (stats->type.value() == "static")
				map.push_back(StaticGameObject(vector3df(stats->posx.value(), stats->posy.value(), stats->posz.value()),
												vector3df(stats->rotx.value(), stats->roty.value(), stats->rotz.value()),
												scnmgr, driver, stats->model.c_str(), stats->texture.c_str(),stats->transparent.value(),
												stats->scale.value()));
			if (stats->type.value() == "billboard")
				map.push_back(BillboardGameObject(vector3df(stats->posx.value(), stats->posy.value(), stats->posz.value()),
												vector3df(stats->rotx.value(), stats->roty.value(), stats->rotz.value()),
												scnmgr, driver, stats->model.c_str(), stats->texture.c_str(), stats->transparent.value(),
												stats->scale.value()));
			for (int j = 0; j < stats->Componants.size(); j++)
			{
				map.back().componants.push_back(factory.createInstance(stats->Componants.getItem(j)->type.value()));
				map.back().componants.back()->XML = stats->Componants.getItem(j);
				map.back().componants.back()->init();
			}
			delete stats;
		}
	}
	return map;
}
