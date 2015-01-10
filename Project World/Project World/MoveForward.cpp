#include "MoveForward.h"
#include "GameObject.h"

DerivedRegister<MoveForward> MoveForward::reg("MoveForward");
void MoveForward::init()
{
	Identifier = "MoveForward";
	RegisterVar(&Speed);
	RegisterVar(&Max);
}
void MoveForward::Update(GameObject *Object)
{
	Object->node->setPosition(Object->node->getPosition() + Object->node->getRotation().rotationToDirection()*0.1f);
	//cout << Speed << endl;
	//cout << Max << endl;
}

