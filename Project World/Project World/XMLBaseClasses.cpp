#include "XMLBaseClasses.h"

bFloat::bFloat()
{
	setClassName("bFloat");
	setVersion("1");

	Register("Float", &Float);
}
bInt::bInt()
{
	setClassName("bInt");
	setVersion("1");

	Register("Int", &Int);
}
bBool::bBool()
{
	setClassName("bBool");
	setVersion("1");

	Register("Bool", &Bool);
}
bString::bString()
{
	setClassName("bString");
	setVersion("1");

	Register("String", &String);
}