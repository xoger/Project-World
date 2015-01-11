#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include <ICursorControl.h>
#include <GameObject.h>
#include <MapLoader.h>
#include <Mover.h>
#include <vector>
#include "EventReceiver.h"
#include "ObjectCreator.h"


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace std;

#ifdef _IRR_WINDOWS_
	//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class Game
{
	IrrlichtDevice * device;
	ISceneManager *scnmgr;
	IVideoDriver *driver;
	ITriangleSelector *triangle = 0;
	ISceneCollisionManager *colmgr;
	irr::gui::ICursorControl *mous;
	EventReceiver receiver;
	vector<GameObject> objects;
	ICameraSceneNode *camera;
	Mover *mover;
	MapLoader *maploader;
	ObjectCreator *objectCreator;
	
	bool draw = true;
public:
	void Start()
	{
		device = createDevice(EDT_DIRECT3D9, dimension2d<u32>(1024,768), 16, false, false, false, &receiver);
		if (device == NULL)
			exit(-1);
		mous = device->getCursorControl();
		scnmgr = device->getSceneManager();
		driver = device->getVideoDriver();
		colmgr = scnmgr->getSceneCollisionManager();
		mover = new Mover(scnmgr,driver,mous,&receiver);
		
		SKeyMap keyMap[8];
			keyMap[1].Action = EKA_MOVE_FORWARD;
			keyMap[1].KeyCode = KEY_KEY_W;
			keyMap[3].Action = EKA_MOVE_BACKWARD;
			keyMap[3].KeyCode = KEY_KEY_S;
			keyMap[5].Action = EKA_STRAFE_LEFT;
			keyMap[5].KeyCode = KEY_KEY_A;
			keyMap[7].Action = EKA_STRAFE_RIGHT;
			keyMap[7].KeyCode = KEY_KEY_D;

		camera = scnmgr->addCameraSceneNodeFPS(NULL,100,1,-1,keyMap,8);
		camera->setFarValue(100000);
		camera->setPosition(vector3df(0, 0, 0));
		camera->setInputReceiverEnabled(false);
		
		maploader = new MapLoader();
		objects = maploader->Start(scnmgr, driver);
		objectCreator = new ObjectCreator(scnmgr, &receiver, &objects, mous, colmgr, camera, driver);
		
		while (device->run())
		{
			Draw();
			Update();
		}
		device->drop();
	}

	int mousepos [2];
	void Update()
	{
		//--Set delta time-//
		static u32 lastframe = device->getTimer()->getTime();
		const u32 thisframe = device->getTimer()->getTime();
		const f32 DeltaTime = (f32)(thisframe - lastframe);
		lastframe = thisframe;
		//--Write FPS--//
		static int frame = 1;
		if (frame == 200)
		{
			//cout << driver->getFPS() << endl;
			frame = 0;
		}
		frame++;
		receiver.Update();
		mover->Update(camera);
		if (receiver.MouseState.RightButtonDown == true){
			if (receiver.MouseState.RightButtonDownOnce == true)
				mous->setPosition(0.5f, 0.5f);
			mous->setVisible(false);
			camera->setInputReceiverEnabled(true);
			for (int i = 0; i < objects.size(); i++)
				objects[i].Update();
		}
		else{
			
			camera->setInputReceiverEnabled(false);
			mous->setVisible(true);
			objectCreator->Update();
			if (receiver.MouseState.LeftButtonDownOnce == true)
				if (mover->SelectArrow(mous, colmgr, camera) == false)
				{
					if (receiver.MouseState.LeftButtonDownOnce == true)
					{
						float shortest = 100000;
						GameObject *collided;
						for (int i = 0; i < objects.size(); i++)
						{
							if (objects[i].node->getType() == ESNT_MESH)
								triangle = scnmgr->createTriangleSelector(objects[i].meshnode->getMesh(), objects[i].node);
							if (objects[i].node->getType() == ESNT_BILLBOARD)
								triangle = scnmgr->createTriangleSelectorFromBoundingBox(objects[i].node);
							float distance = objects[i].isMouseTarget(mous, colmgr, camera, triangle);
							triangle->drop();
							if (distance < shortest)
							{
								if (distance < 100000)
								{
									shortest = distance;
									collided = &objects[i];
								}
							}
						}
						if (shortest < 100000)
							mover->ChangeObject(collided->node);
						else
							mover->ChangeObject(scnmgr->getRootSceneNode());
					}
				}
		}
		if (receiver.IsKeyDown(irr::KEY_KEY_P))
			maploader->Save(&objects);
		if (receiver.IsKeyDown(irr::KEY_ESCAPE))
			device->closeDevice();

	}
	
	void Draw()
	{
		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		if (draw == true)
		{
			scnmgr->drawAll();
			mover->Draw();
		}

		driver->endScene();
	}
};
void main()
{
	Game* game;
	game = new Game();
	game->Start();
}