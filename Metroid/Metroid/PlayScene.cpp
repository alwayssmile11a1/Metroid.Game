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
	//
	//body1.SetSize(34, 66);
	//body1.SetPosition(16 * 30, 16 * 5);
	//body1.SetBodyType(Body::BodyType::Dynamic);


	////body2 = new Body();
	//body2.SetSize(34, 66);
	//body2.SetPosition(16 * 11, 16 * 5);


	sdQuadTree.Load("Resources/map3SDQuadTree.xml", "Resources/map3.tmx");
	//load map
	mapLoader.AddMap("map1", "Resources/map3.tmx",1);
	map = mapLoader.GetMap("map1");
	map->SetCamera(&cam);
	map->SetSpaceDivisionQuadTree(&sdQuadTree);

	//world
	world.SetGravity(-10);
	world.SetContactListener(&worldListener);
	world.SetCamera(&cam);

	std::vector<Shape::Rectangle> rects = map->GetObjectGroup("Platform")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = rects.begin(); rect!= rects.end(); ++rect)
	{
		Platform platform(&world, (*rect).x, (*rect).y, (*rect).width, (*rect).height);
	}

	skreeTexture = Texture("Resources/enemies.png");
	skree.Create(&world, &skreeTexture, 16 * 73, 16*13);

	//zoomer
	zoomerTexture = Texture("Resources/enemies.png");
	zoomer.Create(&world, &zoomerTexture);
}

void PlayScene::HandlePhysics(float dt)
{
	if (input.GetKeyDown(DIK_SPACE))
	{
		skree.OnHitPlayer();
	}

	

	player.HandleInput();

	zoomer.Update(dt);

	skree.Follow(&player);
	//body1.SetVelocity(-2, 0);

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

	skree.Render(batch);

	zoomer.Render(batch);

	//draw bodies
	//world.RenderBodiesDebug(batch);


	//end drawing
	batch->End();

}


void PlayScene::Update(float dt)
{
	HandlePhysics(dt);

	player.Update(dt);

	skree.Update(dt);

	//zoomer.Update(dt);

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
	world.Release();
	player.Release();
	//skreeTexture.Release();

	

	//delete body1;
	//delete body2;
}
