#include "MetroidGame.h"

MetroidGame::MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
	:Game(hInstance, windowName, screenWidth, screenHeight, isFullScreen, frameRate)
{

}
MetroidGame::~MetroidGame()
{
	batch.Release();
}

void MetroidGame::CreateGame()
{
	//create batch to draw everything
	batch.Create();

	//set cam position
	cam.SetPosition(320, 240);

	//set the camera to be used by this batch
	batch.SetCamera(&cam);

	//create character
	characterTexture = Texture("Resources/samusaran_sheet.png");
<<<<<<< HEAD
	object1 = Object(&characterTexture, 16*9, 16*5, 244, 36, 17, 33);
	object2 = Object(&characterTexture, 16*20, 16*5, 244, 36, 17, 33);
	object3 = Object(&characterTexture, 16 * 5, 16 * 5, 244, 36, 17, 33);
=======
	object1 = Object(&characterTexture, 16 * 10, 16 * 5, 244, 36, 17, 33);
	object2 = Object(&characterTexture, 16 * 5, 16 * 5, 244, 36, 17, 33);
	object3 = Object(&characterTexture, 16 * 15, 16 * 5, 244, 36, 17, 33);
>>>>>>> ac665c5e47b83881e298fd6d21eebd9ad601433d

	object1.SetSize(34, 66);
	object2.SetSize(34, 66);
	object3.SetSize(34, 66);

	object1.FitBody();
	object2.FitBody();
	object3.FitBody();

<<<<<<< HEAD
	
	object2.SetVelocity(-0.05, 0);
=======
	object2.SetVelocity(0.05, 0);
>>>>>>> ac665c5e47b83881e298fd6d21eebd9ad601433d

	//setup animation
	TexturePacker p = TexturePacker(&characterTexture, "Resources/samusaran_packer.xml");
	ani.AddRegion(p.GetRegion("charactermove"));
	
	//load map
	mapLoader.AddMap("map1", "Resources/map1.tmx");
	map = mapLoader.GetMap("map1");
	map->SetCamera(&cam);

	//world = World(9.8);
	world.AddBody(&object1.GetBody());
	world.AddBody(&object2.GetBody());
	world.AddBody(&object3.GetBody());

	
	world.AddBody(map->GetObjectGroup("Object Layer 1")->GetBodies());

}

void MetroidGame::UpdateGame(float dt)
{
	if (input.GetKey(DIK_RIGHT))
	{
		object1.GetBody().ApplyLinearImpulse(0.2, 0);
		object1.SetRegion(ani.Next(dt, true));
	}        

	if (input.GetKey(DIK_LEFT))
	{
		object1.GetBody().ApplyLinearImpulse(-0.2, 0);
		object1.SetRegion(ani.Next(dt, false));
	}

	object1.Update(dt);


	if (object1.GetPosition().x > cam.GetPosition().x)
	{
		cam.SetPosition(object1.GetPosition().x, cam.GetPosition().y);
	}

	if (object1.GetPosition().x < cam.GetPosition().x - 250 && cam.GetPosition().x>320)
	{
		cam.SetPosition(cam.GetPosition().x - dt*0.2, cam.GetPosition().y);
	}

	if (input.GetKey(DIK_UP))
	{	
		cam.SetPosition(cam.GetPosition().x, cam.GetPosition().y + +dt*0.2);
	}

	if (input.GetKey(DIK_DOWN))
	{
		cam.SetPosition(cam.GetPosition().x, cam.GetPosition().y - dt * 0.2);
	}

	if (input.GetKeyDown(DIK_ESCAPE))
	{
		ShutDownApplication();
	}

	//Update world
	world.Update(dt);

	//start drawing
	batch.Begin();
	
	//render map
	map->Render(batch);

	//
	batch.Draw(object1);
	batch.Draw(object2);
	batch.Draw(object3);

	//
	world.RenderBodiesDebug(batch);

	//end drawing
	batch.End();

}
