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


	object1 = Object(&characterTexture, 16 * 8, 16 * 5, 244, 36, 17, 33);
	object2 = Object(&characterTexture, 16 * 30, 16 * 5, 244, 36, 17, 33);
	object3 = Object(&characterTexture, 16 * 11, 16 * 5, 244, 36, 17, 33);

	object1.SetSize(34, 66);
	object2.SetSize(34, 66);
	object3.SetSize(34, 66);

	object1.FitBody();
	object2.FitBody();
	object3.FitBody();

	object1.GetBody().SetBodyType(Body::BodyType::Dynamic);
	object1.GetBody().SetLinearDrag(10, 0.2);
	object1.GetBody().SetMass(2);
	object1.GetBody().SetID("Player");

	foot.SetSize(25, 20);
	foot.IsTrigger(true);
	foot.SetID("Foot");

	object2.GetBody().SetBodyType(Body::BodyType::Dynamic);

	//setup animation
	TexturePacker p = TexturePacker(&characterTexture, "Resources/samusaran_packer.xml");
	ani.AddRegion(p.GetRegion("charactermove"));
	
	//load map
	mapLoader.AddMap("map1", "Resources/map2.tmx");
	map = mapLoader.GetMap("map1");
	map->SetCamera(&cam);

	world.SetGravity(-10);
	world.AddBody(&object1.GetBody());
	world.AddBody(&object2.GetBody());
	world.AddBody(&object3.GetBody());
	world.AddBody(&foot);
	world.SetContactListener(this);


	
	world.AddBody(map->GetObjectGroup("Land")->GetBodies());
	world.AddBody(map->GetObjectGroup("Wall 1")->GetBodies());
	world.AddBody(map->GetObjectGroup("Wall 2")->GetBodies());
	world.AddBody(map->GetObjectGroup("Wall 3")->GetBodies());
	world.AddBody(map->GetObjectGroup("Platform 1")->GetBodies());
	world.AddBody(map->GetObjectGroup("Platform 2")->GetBodies());

}

void MetroidGame::HandlePhysics(float dt)
{
	//object1.GetBody().SetVelocity(0, -100000);
	if (input.GetKey(DIK_RIGHT))
	{
		object1.GetBody().SetVelocity(5, object1.GetBody().GetVelocity().y);
		object1.SetRegion(ani.Next(dt, true));
	}

	if (input.GetKey(DIK_LEFT))
	{
		object1.GetBody().SetVelocity(-5, object1.GetBody().GetVelocity().y);
		object1.SetRegion(ani.Next(dt, false));
	}

	if (input.GetKeyDown(DIK_SPACE) && isGrounded && !isJumped)
	{
		object1.GetBody().SetVelocity(object1.GetBody().GetVelocity().x, 8);
		isGrounded = false;
		isJumped = true;
	}

	object2.SetVelocity(-2, 0);

	//Update world
	world.Update(dt);
	
	if (isJumped)
	{
		isGrounded = false;
		isJumped = false;
	}

}

void  MetroidGame::Render()
{
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

void MetroidGame::UpdateGame(float dt)
{
	HandlePhysics(dt);


	if (object1.GetPosition().x > cam.GetPosition().x)
	{
		cam.SetPosition(object1.GetPosition().x, cam.GetPosition().y);
	}

	if (object1.GetPosition().x < cam.GetPosition().x- 250)
	{
		cam.SetPosition(object1.GetPosition().x + 250, cam.GetPosition().y);
		if (cam.GetPosition().x < 320) cam.SetPosition(320, cam.GetPosition().y);
	}
	
	if (input.GetKey(DIK_UP))
	{	
		cam.SetPosition(cam.GetPosition().x, cam.GetPosition().y + +dt*200);
	}

	if (input.GetKey(DIK_DOWN))
	{
		cam.SetPosition(cam.GetPosition().x, cam.GetPosition().y - dt * 200);
	}

	if (input.GetKeyDown(DIK_ESCAPE))
	{
		ShutDownApplication();
	}


	object1.Update(dt);

	foot.SetPosition(object1.GetBody().GetPosition().x, object1.GetBody().GetPosition().y - 30);


	Render();

}

void MetroidGame::OnContact(const Body &bodyA, const Body &bodyB)
{
	if (bodyA.GetID()._Equal("Foot") && !bodyB.GetID()._Equal("Player"))
	{
		isGrounded = true;
	}
}
