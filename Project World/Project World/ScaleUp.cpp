#include "ScaleUp.h"
#include "GameObject.h"

DerivedRegister<ScaleUp> ScaleUp::reg("ScaleUp");
void ScaleUp::init()
{
	Identifier = "ScaleUp";
	//Speed = speed;
}
void ScaleUp::Update(GameObject *Object)
{
	Object->node->setScale(Object->node->getScale() + 0.1f);
}

