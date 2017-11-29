#include "PlayScene.h"



PlayScene::PlayScene()
{
}


PlayScene::~PlayScene()
{
}

void PlayScene::SetBatch(SpriteBatch* batch)
{
	this->batch = batch;
	//set the camera to be used by this batch
	batch->SetCamera(&cam);
}

void PlayScene::Create()
{
	//set cam position
	cam.SetPosition(320, 240);

	player.Create(&world);

	//object examples
	//body1 = new Body();
	body1.SetSize(34, 66);
	body1.SetPosition(16 * 30, 16 * 5);
	body1.SetBodyType(Body::BodyType::Dynamic);


	//body2 = new Body();
	body2.SetSize(34, 66);
	body2.SetPosition(16 * 11, 16 * 5);



	//load map
	mapLoader.AddMap("map1", "Resources/map2.tmx");
	map = mapLoader.GetMap("map1");
	map->SetCamera(&cam);


	//world
	world.SetGravity(-10);
	world.AddBody(&body1);
	world.AddBody(&body2);

	world.SetContactListener(&worldListener);
	
	world.AddBody(map->GetObjectGroup("Platform")->GetBodies());

}

void PlayScene::HandlePhysics(float dt)
{
	player.HandleInput();

	body1.SetVelocity(-2, 0);

	//Update world
	world.Update(dt);

}

void  PlayScene::Render()
{
	//start drawing
	batch->Begin();

	//render map
	map->Render(batch);
	
	player.Render(batch);


	//draw bodies
	world.RenderBodiesDebug(batch);

	//end drawing
	batch->End();
}


void PlayScene::Update(float dt)
{
	HandlePhysics(dt);

	player.Update(dt);


	if (player.GetPosition().x > cam.GetPosition().x)
	{
		cam.SetPosition(player.GetPosition().x, cam.GetPosition().y);
	}

	if (player.GetPosition().x < cam.GetPosition().x - 250)
	{
		cam.SetPosition(player.GetPosition().x + 250, cam.GetPosition().y);
		if (cam.GetPosition().x < 320) cam.SetPosition(320, cam.GetPosition().y);
	}

	//if (input.GetKey(DIK_UP))
	//{
	//	cam.SetPosition(cam.GetPosition().x, cam.GetPosition().y + +dt * 200);
	//}

	//if (input.GetKey(DIK_DOWN))
	//{
	//	cam.SetPosition(cam.GetPosition().x, cam.GetPosition().y - dt * 200);
	//}

	Render();
}

void PlayScene::Release()
{
	player.Release();
	//delete body1;
	//delete body2;
}
