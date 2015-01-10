#ifndef ObjectComponant_H_INCLUDED
#define ObjectComponant_H_INCLUDED
#include "Globals.h"
#include <vector>
#include <string>
#include <XMLSerialization.h>
#include <irrlicht.h>
#include "XMLBaseClasses.h"
#include <iostream>
using namespace xmls;
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace std;

class GameObject;
class XMLObjectComponant : public Serializable
{
public:
	Collection < bFloat > floats;
	Collection < bInt > ints;
	Collection < bString > strings;
	Collection < bBool > bools; 
	xString type;
	XMLObjectComponant();
};
class ObjectComponant
{
public:
	std::string Identifier;
	virtual void Update(GameObject *Object) = 0;
	virtual void init() = 0;
	vector<int*> ints;
	vector<float*> floats;
	vector<std::string*> strings;
	vector<bool*> bools;
	XMLObjectComponant *XML = new XMLObjectComponant();
	void updateXMLvars();
	//--fetches variable from xmlcomponant
	void RegisterVar(float *f);
	void RegisterVar(int *i);
	void RegisterVar(std::string *s);
	void RegisterVar(bool *b);

	vector<bInt> XMLints = vector<bInt>();
};
//---Not written by me, written by Albert from http://mydov.blogspot.co.uk/, from here--//
template<typename T> ObjectComponant * createT() { return new T; }
struct ComponantFactory 
{
	typedef std::map<std::string, ObjectComponant*(*)()> map_type;

	static ObjectComponant * createInstance(std::string const& s) 
	{
		map_type::iterator it = getMap()->find(s);
		if (it == getMap()->end())
			return 0;
		return it->second();
	}
protected:
	static map_type * getMap() 
	{
		if (!map) {	map = new map_type; }
		return map;
	}
private:
	static map_type * map;
};
template<typename T>
struct DerivedRegister : ComponantFactory {
	DerivedRegister(std::string const& s) {
		getMap()->insert(std::make_pair(s, &createT<T>));
	}
};
//---To here---//
#endif