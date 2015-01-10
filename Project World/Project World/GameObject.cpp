#include <GameObject.h>
#include <iostream>

 void GameObject::init(vector3df position, vector3df rotation, ISceneManager *scnmgr, IVideoDriver *driver, irr::io::path mesh, irr::io::path texture, bool transparent, float scale)
 {
	 modelname = mesh.c_str();
	 texname = texture.c_str();
	 this->transparent = transparent;
	 node->setMaterialTexture(0, driver->getTexture(texture));
	 node->setMaterialType(EMT_SOLID);
	 node->setMaterialFlag(EMF_LIGHTING, false);
	 node->setScale(vector3df(scale, scale, scale));
	 if (transparent == true)
	 {
		 node->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
	 }
	 node->setPosition(position);
	 node->setRotation(rotation);
 }
 void GameObject::Update()
 {
	 for (int i = 0; i < componants.size(); i++)
	 {
		 componants[i]->Update(this);
	 }
 }
 float GameObject::isMouseTarget(irr::gui::ICursorControl *mous, ISceneCollisionManager *colmgr, ICameraSceneNode *camera, ITriangleSelector *triangle)
{
	aabbox3d<f32> camerabox = aabbox3d<f32>(camera->getPosition());
	line3df line = colmgr->getRayFromScreenCoordinates(mous->getPosition(),camera);

	ISceneNode *collnode;
	triangle3df colltri;
	colmgr->getCollisionPoint(line, triangle, collpoint, colltri, collnode);
	if (collnode == node)

		return collpoint.getDistanceFrom(camera->getPosition());
	else
		return 100000;
}
AnimatedGameObject::AnimatedGameObject(vector3df position, vector3df rotation, ISceneManager *scnmgr, IVideoDriver *driver, irr::io::path mesh, irr::io::path texture, bool transparent, float scale)
{
	
}
BillboardGameObject::BillboardGameObject(vector3df position, vector3df rotation, ISceneManager *scnmgr, IVideoDriver *driver, irr::io::path mesh, irr::io::path texture, bool transparent, float scale)
{
	billnode = scnmgr->addBillboardSceneNode();
	billnode->setSize(dimension2d<f32>(driver->getTexture(texture)->getSize().Width*scale, driver->getTexture(texture)->getSize().Height*scale));
	this->type = "billboard";
	billnode->setName(texture);
	node = scnmgr->getSceneNodeFromName(texture.c_str(),billnode);
	init(position, rotation, scnmgr, driver, mesh, texture, transparent, scale);
}
StaticGameObject::StaticGameObject(vector3df position, vector3df rotation, ISceneManager *scnmgr, IVideoDriver *driver, irr::io::path mesh, irr::io::path texture, bool transparent, float scale)
{
	model = scnmgr->getMesh(mesh);
	meshnode = scnmgr->addMeshSceneNode(model);
	this->type = "static";
	meshnode->setName(texture);
	node = scnmgr->getSceneNodeFromName(texture.c_str(),meshnode);	
	init(position, rotation, scnmgr, driver, mesh, texture, transparent, scale);
}
