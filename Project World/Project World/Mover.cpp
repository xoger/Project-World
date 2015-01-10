#include "Mover.h"
#include <iostream>
using namespace std;
Mover::Mover(ISceneManager *Scnmgr, IVideoDriver *Driver, irr::gui::ICursorControl *Mous, EventReceiver* Receiver)
{
	mous = Mous;
	scnmgr = Scnmgr;
	driver = Driver;
	receiver = Receiver;
	XYZ[0] = scnmgr->addMeshSceneNode(scnmgr->getMesh("axis/X.obj"));
	XYZ[1] = scnmgr->addMeshSceneNode(scnmgr->getMesh("axis/Y.obj"));
	XYZ[2] = scnmgr->addMeshSceneNode(scnmgr->getMesh("axis/Z.obj"));

	XYZ[0]->setMaterialTexture(0, driver->getTexture("axis/Red.png"));
	XYZ[1]->setMaterialTexture(0, driver->getTexture("axis/Green.png"));
	XYZ[2]->setMaterialTexture(0, driver->getTexture("axis/Blue.png"));

	directions[0] = vector3df(-1, 0, 0);
	directions[1] = vector3df(0, 1, 0);
	directions[2] = vector3df(0, 0, 1);
	selected = scnmgr->getRootSceneNode();
	object = scnmgr->getRootSceneNode();
	for (int i = 0; i < _countof(XYZ); i++)
	{
		XYZ[i]->setMaterialFlag(EMF_LIGHTING, false);
	}
}
void Mover::Update(ICameraSceneNode *camera)
{
	if (object == scnmgr->getRootSceneNode())
		draw = false;
	else
		draw = true;
	if (draw == true)
	{
		pos = vector3df(object->getTransformedBoundingBox().MinEdge.X,
						object->getTransformedBoundingBox().MaxEdge.Y,
						object->getTransformedBoundingBox().MaxEdge.Z);
		f32 distance = (camera->getPosition().getDistanceFrom(pos)) / 80;
		float ypos = mous->getPosition().Y;
		static float yposold;
		for (int i = 0; i < _countof(XYZ); i++)
		{
			XYZ[i]->setScale(vector3df(distance, distance, distance));
			XYZ[i]->setPosition(pos);

			if (selected == XYZ[i])
				if (receiver->MouseState.LeftButtonDown == false)
					selected = scnmgr->getRootSceneNode();
				else
					object->setPosition(object->getPosition() + (directions[i] * -(ypos - yposold) * distance *0.5f));
		}
		yposold = ypos;
	}
}
bool Mover::SelectArrow(irr::gui::ICursorControl *mous, ISceneCollisionManager *colmgr, ICameraSceneNode *camera)
{
	aabbox3d<f32> camerabox = aabbox3d<f32>(camera->getPosition());
	line3df line = colmgr->getRayFromScreenCoordinates(mous->getPosition(), camera);
	for (int i = 0; i < _countof(XYZ); i++)
	{
		triangle = scnmgr->createTriangleSelectorFromBoundingBox(XYZ[i]);
		vector3df collpoint;
		ISceneNode *collnode;
		triangle3df colltri;
		colmgr->getCollisionPoint(line, triangle, collpoint, colltri, collnode);
		triangle->drop();
		
		if (collnode == XYZ[i])
			selected = XYZ[i];
		else
			selected = scnmgr->getRootSceneNode();
		if (collnode == XYZ[i])
			return true;
	}
	return false;
}
void Mover::ChangeObject(ISceneNode *node)
{
	if (object == scnmgr->getRootSceneNode())
		object = node;
	else
		object = scnmgr->getRootSceneNode();
}
void Mover::Draw()
{
	if (draw == true)
	{
		ITexture* tex = object->getMaterial(0).getTexture(0);
		
		bool transparent;
		if (object->getMaterial(0).MaterialType == EMT_TRANSPARENT_ALPHA_CHANNEL)
			transparent = true;
		else
			transparent = false;
		object->setMaterialFlag(EMF_WIREFRAME, true);
		object->setMaterialType(EMT_SOLID);
		object->setMaterialTexture(0, driver->getTexture("axis/Red.png"));
		driver->clearZBuffer();
		object->render();
		object->setMaterialFlag(EMF_WIREFRAME, false);
		object->setMaterialTexture(0, tex);
		if (transparent == true)
			object->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
			
		driver->clearZBuffer();
		for (int i = 0; i < _countof(XYZ); i++)
		{
			XYZ[i]->setVisible(true);
			XYZ[i]->render();
		}
	}
	else
		for (int i = 0; i < _countof(XYZ); i++)
		{
			XYZ[i]->setVisible(false);
		}
}


