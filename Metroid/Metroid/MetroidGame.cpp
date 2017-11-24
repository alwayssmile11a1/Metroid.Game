#include "MetroidGame.h"

CSound *BrinstarTheme = NULL;
CSound *Jump = NULL;

MetroidGame::MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
	:Game(hInstance, windowName, screenWidth, screenHeight, isFullScreen, frameRate)
{

}
MetroidGame::~MetroidGame()
{

}

void MetroidGame::Release()
{
	Game::Release();
	batch.Release();
	player.Release();
	delete body1;
	delete body2;
	delete worldListener;
}

void MetroidGame::CreateGame()
{
	//create batch to draw everything
	batch.Create();

	//set cam position
	cam.SetPosition(320, 240);

	//set the camera to be used by this batch
	batch.SetCamera(&cam);

	player.Create(world);

	//object examples
	body1 = new Body();
	body1->SetSize(34, 66);
	body1->SetPosition(16 * 30, 16 * 5);
	body1->SetBodyType(Body::BodyType::Dynamic);


	body2 = new Body();
	body2->SetSize(34, 66);
	body2->SetPosition(16 * 11, 16 * 5);



	//load map
	mapLoader.AddMap("map1", "Resources/map2.tmx");
	map = mapLoader.GetMap("map1");
	map->SetCamera(&cam);


	//world
	world.SetGravity(-10);
	world.AddBody(body1);
	world.AddBody(body2);

	worldListener = new WorldListener();
	world.SetContactListener(worldListener);


	world.AddBody(map->GetObjectGroup("Platform")->GetBodies());


	//load sound brinstar theme
	BrinstarTheme = sound.LoadSound("Resources/BrinstarTheme.wav");
	//play sound brinstar theme
	sound.PlaySound(BrinstarTheme);

}

void MetroidGame::HandlePhysics(float dt)
{
	player.HandleInput(dt);

	body1->SetVelocity(-2, 0);

	//Update world
	world.Update(dt);
 	if (player.isJumping)
	{
		player.isGrounded = false;
		player.isJumping = false;
	}

}

void  MetroidGame::Render()
{
	//start drawing
	batch.Begin();

	//render map
	map->Render(batch);

	//
	batch.Draw(player);
	//batch.Draw(object2);
	//batch.Draw(object3);

	//
	world.RenderBodiesDebug(batch);

	//end drawing
	batch.End();
}

void MetroidGame::UpdateGame(float dt)
{
	HandlePhysics(dt);
	
	player.Update(dt);

	if (player.GetPosition().x > cam.GetPosition().x)
	{
		cam.SetPosition(player.GetPosition().x, cam.GetPosition().y);
	}

	if (player.GetPosition().x < cam.GetPosition().x- 250)
	{
		cam.SetPosition(player.GetPosition().x + 250, cam.GetPosition().y);
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


	player.foot->SetPosition(player.GetBody()->GetPosition().x, player.GetBody()->GetPosition().y - 30);


	Render();

}

