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

	
	//bullet texture
	bulletTexture = Texture("Resources/samusaran_sheet.png");
}

void PlayScene::HandlePhysics(float dt)
{
	if (input.GetKey(DIK_RIGHT))
	{
		player.GetMainBody()->SetVelocity(5, player.GetMainBody()->GetVelocity().y);
	}

	if (input.GetKey(DIK_LEFT))
	{
		player.GetMainBody()->SetVelocity(-5, player.GetMainBody()->GetVelocity().y);

	}

	if (input.GetKeyDown(DIK_Z) && player.isGrounded && !player.isJumping)
	{
		player.GetMainBody()->SetVelocity(player.GetMainBody()->GetVelocity().x, 8);
		player.isGrounded = false;
		player.isJumping = true;
	}

	if (input.GetKey(DIK_UPARROW))
	{
		player.isLookingup = true;
	}
	else
	{
		player.isLookingup = false;
	}

	if (input.GetKeyDown(DIK_X))
	{
		player.isShooting = true;
	}

	if (input.GetKey(DIK_X))
	{
		player.isShooting = true;
	}
	else
	{
		player.isShooting = false;
	}

	if (player.isShooting)
	{
		Bullet* bullet = new Bullet(&world, &bulletTexture);
		Vector2 position;
		Vector2 velocity;
		if (player.isLookingup)
		{
			position.x = player.GetPosition().x;
			position.y = player.GetPosition().y + player.GetSize().y/2 + bullet->GetSize().y/2;
			velocity.Set(0, 4);
		}
		else
		{
			if (!player.IsFlipX())
			{
				position.x = player.GetPosition().x + player.GetSize().x / 2 + bullet->GetSize().x / 2;
				position.y = player.GetPosition().y + 10;
				velocity.Set(4, 0);
			}
			else
			{
				position.x = player.GetPosition().x - player.GetSize().x / 2 - bullet->GetSize().x / 2;
				position.y = player.GetPosition().y + 10;
				velocity.Set(-4, 0);
			}
		}

		bullet->GetMainBody()->SetPosition(position.x, position.y);
		bullet->SetVelocity(velocity.x,velocity.y);
		bullets.push_back(bullet);
	}


	body1.SetVelocity(-2, 0);

	//Update world
	world.Update(dt);


}

void  PlayScene::Render()
{
	//start drawing
	batch->Begin();

	//render map
	map->Render(*batch);
	
	//draw bullets
	for (std::list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
	{
		(*it)->Render(*batch);
	}

	//draw player
	batch->Draw(player);


	//draw bodies
	world.RenderBodiesDebug(*batch);

	//end drawing
	batch->End();
}


void PlayScene::Update(float dt)
{
	HandlePhysics(dt);

	player.Update(dt);

	//update
	std::list<Bullet*> destroyedBullets;
	for (std::list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
	{
		(*it)->Update(dt);
		if ((*it)->IsDestroyed())
		{
			destroyedBullets.push_back((*it));
		}
	}

	//delete destroyed bullets
	for (std::list<Bullet*>::iterator it = destroyedBullets.begin(); it != destroyedBullets.end(); ++it)
	{
		bullets.remove(*it);
		delete *it;
	}

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
	//draw bullets
	for (std::list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
	{
		delete (*it);
	}
	bulletTexture.Release();
	//delete body1;
	//delete body2;
}
