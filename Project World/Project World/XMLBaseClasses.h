#ifndef BaseClasses_H_INCLUDED
#define BaseClasses_H_INCLUDED
#include <XMLSerialization.h>
#include <string>
using namespace xmls;
class bFloat : public Serializable
{
public:
	xFloat Float;
	bFloat();
};
class bInt : public Serializable
{
public:
	xInt Int;
	bInt();
};
class bBool : public Serializable
{
public:
	xBool Bool;
	bBool();
}; 
class bString : public Serializable
{
public:
	xString String;
	bString();
};
#endif

