#include "ObjectComponant.h"
#include "GameObject.h"
#include "Globals.h"
void ObjectComponant::RegisterVar(int *i)
{ 
	static int j = 0;
	ints.push_back(i);
	if (j<XML->ints.size()){
		*i = XML->ints.getItem(j)->Int.value();
	j++; }
	else
		~j;
};
void ObjectComponant::RegisterVar(float *f)
{
	static int j = 0;
	floats.push_back(f);
	if (j < XML->floats.size()){
		*f = XML->floats.getItem(j)->Float.value();
		j++;
	}
	else
		~j;
};
void ObjectComponant::RegisterVar(bool *b)
{
	static int j = 0;
	bools.push_back(b);
	if (j < XML->bools.size()) {
		*b = XML->bools.getItem(j)->Bool.value();
		j++;
	}
	else
		~j;
};
void ObjectComponant::RegisterVar(std::string *s)
{ 
	static int j = 0;
	strings.push_back(s);

	if (j < XML->strings.size())
	{
		*s = XML->strings.getItem(j)->String.value();
		j++;
	}
	else
		~j;
};

void ObjectComponant::updateXMLvars()
{
	XML = new XMLObjectComponant();
	XML->type = Identifier;
	
	for (int i = 0; i < ints.size(); i++){
		bInt *b = new bInt();
		xInt x = *ints[i];
		b->Int = x;
		XML->ints.addItem(b);
	}
	for (int i = 0; i < floats.size(); i++){
		bFloat *b = new bFloat();
		xFloat x = *floats[i];
		b->Float = x;
		XML->floats.addItem(b);
	}
	for (int i = 0; i < strings.size(); i++){
		bString *b = new bString();
		xString x = *strings[i];
		b->String = x;
		XML->strings.addItem(b);
	}
	for (int i = 0; i < bools.size(); i++){
		bBool *b = new bBool();
		xBool x = *bools[i];
		b->Bool = x;
		XML->bools.addItem(b);
	}
}
XMLObjectComponant::XMLObjectComponant()
{
	setClassName("XMLObjectComponant");
	setVersion("1");

	Register("floats", &floats);
	Register("ints", &ints);
	Register("strings", &strings);
	Register("bools", &bools);
	Register("type", &type);
}

