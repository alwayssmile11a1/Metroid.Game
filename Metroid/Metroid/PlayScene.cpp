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
	stateTime = 0;

	sdQuadTree.Load("Resources/map3SDQuadTree.xml", "Resources/map3.tmx");
	//load map
	mapLoader.AddMap("map1", "Resources/map3.tmx",1);
	map = mapLoader.GetMap("map1");
	map->SetCamera(&cam);
	map->SetSpaceDivisionQuadTree(&sdQuadTree);

	//world
	world.SetGravity(-20);
	world.SetContactListener(&worldListener);
	world.SetCamera(&cam);

	//create platform
	std::vector<Shape::Rectangle> platformRects = map->GetObjectGroup("Platform")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = platformRects.begin(); rect!= platformRects.end(); ++rect)
	{
		Platform platform(&world, rect->x, rect->y, rect->width, rect->height);
	}

	//create breakableplatform
	std::vector<Shape::Rectangle> breakablePlatformRects = map->GetObjectGroup("BreakablePlatform")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = breakablePlatformRects.begin(); rect != breakablePlatformRects.end(); ++rect)
	{
		BreakablePlatform* breakablePlatform = new BreakablePlatform(&world,map, rect->x, rect->y, rect->width, rect->height);
		breakablePlatforms.push_back(breakablePlatform);
	}

	//get player position
	Shape::Rectangle playerRect = map->GetObjectGroup("Player")->GetRects().front();
	player.Create(&world, playerRect.x,playerRect.y);

	//set cam position
	cam.SetPosition(playerRect.x, playerRect.y + 110);

	//Doors
	doorTexture = Texture("Resources/spriteobjects.png");
	std::vector<Shape::Rectangle> doorRects = map->GetObjectGroup("Door")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = doorRects.begin(); rect != doorRects.end(); ++rect)
	{
		Door *door = new Door();
		door->Create(&world, &doorTexture, rect->x , rect->y);
		doors.push_back(door);
	}

	//--------------------------ENEMIES-------------------------------
	enemiesTexture = Texture("Resources/enemies.png");

	//skree
	std::vector<Shape::Rectangle> skreeRects = map->GetObjectGroup("Skree")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = skreeRects.begin(); rect != skreeRects.end(); ++rect)
	{
		Skree *skree = new Skree();
		skree->Create(&world, &enemiesTexture, rect->x, rect->y);
		skrees.push_back(skree);
	}

	//zoomer
	std::vector<Shape::Rectangle> zoomerRects = map->GetObjectGroup("Zoomer")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = zoomerRects.begin(); rect != zoomerRects.end(); ++rect)
	{
		Zoomer *zoomer = new Zoomer();
		zoomer->Create(&world, &enemiesTexture, rect->x, rect->y, true);

		zoomers.push_back(zoomer);
	}
	
	//rio
	std::vector<Shape::Rectangle> rioRects = map->GetObjectGroup("Rio")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = rioRects.begin(); rect != rioRects.end(); ++rect)
	{
		Rio *rio = new Rio();
		rio->Create(&world, &enemiesTexture, rect->x, rect->y);

		rios.push_back(rio);
	}

	//ripper
	std::vector<Shape::Rectangle> ripperRects = map->GetObjectGroup("Ripper")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = ripperRects.begin(); rect != ripperRects.end(); ++rect)
	{
		Ripper *ripper = new Ripper();
		ripper->Create(&world, &enemiesTexture, rect->x, rect->y);
		rippers.push_back(ripper);
	}


	//--------------------------BOSSES-------------------------------
	bossesTexture = Texture("Resources/bosses.png");
	//Mother Brai
	Shape::Rectangle motherBrainRect = map->GetObjectGroup("MotherBrain")->GetRects().front();
	motherBrain = new MotherBrain();
	motherBrain->Create(&world, &bossesTexture, motherBrainRect.x, motherBrainRect.y);

	//Kraid 
	Shape::Rectangle kraidRect = map->GetObjectGroup("Kraid")->GetRects().front();
	kraid = new Kraid();
	kraid->Create(&world, &bossesTexture, &player, kraidRect.x, kraidRect.y);

	//Cannons
	std::vector<Shape::Rectangle> leftCannonRects = map->GetObjectGroup("LeftCannon")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = leftCannonRects.begin(); rect != leftCannonRects.end(); ++rect)
	{
		Cannon *cannon = new Cannon();
		cannon->Create(&world, &bossesTexture,Cannon::Type::Left, rand()%8, rect->x, rect->y);

		cannons.push_back(cannon);
	}
	std::vector<Shape::Rectangle> rightCannonRects = map->GetObjectGroup("RightCannon")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = rightCannonRects.begin(); rect != rightCannonRects.end(); ++rect)
	{
		Cannon *cannon = new Cannon();
		cannon->Create(&world, &bossesTexture, Cannon::Type::Right, rand() % 8, rect->x, rect->y);

		cannons.push_back(cannon);
	}
	std::vector<Shape::Rectangle> topCannonRects = map->GetObjectGroup("TopCannon")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = topCannonRects.begin(); rect != topCannonRects.end(); ++rect)
	{
		Cannon *cannon = new Cannon();
		cannon->Create(&world, &bossesTexture, Cannon::Type::Top, rand() % 8, rect->x, rect->y);

		cannons.push_back(cannon);
	}
	
	//CircleCannons
	std::vector<Shape::Rectangle> circleCannonRects = map->GetObjectGroup("CircleCannon")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = circleCannonRects.begin(); rect != circleCannonRects.end(); ++rect)
	{
		CircleCannon *cannon = new CircleCannon();
		cannon->Create(&world, &enemiesTexture,&player, rect->x, rect->y);

		circleCannons.push_back(cannon);
	}

	//HealthPiles
	std::vector<Shape::Rectangle> healthPileRects = map->GetObjectGroup("HealthPile")->GetRects();
	for (std::vector<Shape::Rectangle>::iterator rect = healthPileRects.begin(); rect != healthPileRects.end(); ++rect)
	{
		HealthPile *healthPile = new HealthPile();
		healthPile->Create(&world, &bossesTexture, rect->x, rect->y);

		healthPiles.push_back(healthPile);
	}




	//---------------------------ITEMS------------------------------------
	itemsTexture = Texture("Resources/items.png");

	//roll ability item
	Shape::Rectangle rollItemRect = map->GetObjectGroup("MaruMariItem")->GetRects().front();
	maruMariItem.Create(&world, &itemsTexture, rollItemRect.x, rollItemRect.y);

	//bomb ability item
	Shape::Rectangle bombItemRect = map->GetObjectGroup("BombItem")->GetRects().front();
	bombItem.Create(&world, &itemsTexture, bombItemRect.x, bombItemRect.y);

	//effects
	effectsTexture = Texture("Resources/metroidfullsheet.png");
	explosionEffect.Create(&effectsTexture);
	explosionEffect.SetSize(24, 24);

	//--------------------------UI--------------------------------------
	font = Font("Arial", 10, 30);
	playerHealthLabel = Label("30", &font, cam.GetPosition().x-250, cam.GetPosition().y+300, 640, 480);


	//BrinstarTheme Sound
	BrinstarTheme = Sound::LoadSound("Resources/SoundEffect/BrinstarTheme.wav");
	
}

void PlayScene::HandlePhysics(float dt)
{
	//handle input of player
	player.HandleInput();
	
	//handle physics skrees
	for (std::vector<Skree*>::iterator it = skrees.begin(); it != skrees.end(); ++it)
	{
		(*it)->HandlePhysics(&player);
	}

	//handle physics zoomers
	for (std::vector<Zoomer*>::iterator it = zoomers.begin(); it != zoomers.end(); ++it)
	{
		(*it)->HandlePhysics();
	}

	//handle physics rios
	for (std::vector<Rio*>::iterator it = rios.begin(); it != rios.end(); ++it)
	{
		(*it)->HandlePhysics(&player);
	}

	if (kraid != NULL)
	{
		kraid->HandlePhysics();
	}


	//Update world
	world.Update(dt);


}

void  PlayScene::Render()
{
	//start drawing
	batch->Begin();

	//render player
	player.Render(batch);

	//render doors
	for (std::vector<Door*>::iterator it = doors.begin(); it != doors.end(); ++it)
	{
		(*it)->Render(batch);
	}

	//render skrees
	for (std::vector<Skree*>::iterator it = skrees.begin(); it != skrees.end(); ++it)
	{
		(*it)->Render(batch);
	}

	//render zoomers
	for (std::vector<Zoomer*>::iterator it = zoomers.begin(); it != zoomers.end(); ++it)
	{
		(*it)->Render(batch);
	}

	//render rios
	for (std::vector<Rio*>::iterator it = rios.begin(); it != rios.end(); ++it)
	{
		(*it)->Render(batch);
	}

	//render rippers
	for (std::vector<Ripper*>::iterator it = rippers.begin(); it != rippers.end(); ++it)
	{
		(*it)->Render(batch);
	}


	//kraid
	if (kraid != NULL)
	{
		kraid->Render(batch);
	}

	//mother brain
	if (motherBrain != NULL)
	{
		motherBrain->Render(batch);
	}
	//render cannons
	for (std::vector<Cannon*>::iterator it = cannons.begin(); it != cannons.end(); ++it)
	{
		(*it)->Render(batch);
	}

	//render circle cannons
	for (std::vector<CircleCannon*>::iterator it = circleCannons.begin(); it != circleCannons.end(); ++it)
	{
		(*it)->Render(batch);
	}

	//render healthPiles
	for (std::vector<HealthPile*>::iterator it = healthPiles.begin(); it != healthPiles.end(); ++it)
	{
		(*it)->Render(batch);
	}

	
	//draw items
	batch->Draw(maruMariItem);
	batch->Draw(bombItem);


	for (std::vector<HealthItem*>::iterator it = healthItems.begin(); it != healthItems.end(); ++it)
	{
		(*it)->Render(batch);
	}
	
	explosionEffect.Render(batch);

	//draw bodies
	world.RenderBodiesDebug(batch);

	//render map
	map->Render(batch);

	//end drawing
	batch->End();
	

	//Label
	playerHealthLabel.Draw(&cam);
}


void PlayScene::Update(float dt)
{
	if (stateTime < PLAYERAPPEARINGTIME) //On player appearing, don't do anything except rendering
	{
		stateTime += dt;
		player.OnAppearing(dt);
		Render();
		return;
	}

	HandlePhysics(dt);

	player.Update(dt);

	//update skrees
	for (int i= 0; i < skrees.size(); i++) //not use iterator for the sake of erase dead skree (we can't delete an element in skrees if we use iterator loop) 
	{
		Skree* skree = skrees[i];
		skree->Update(dt);
		if (skree->IsDead())
		{
			if (skree->GetHealth()<=0)
			{
				explosionEffect.SetSize(32, 32);
				explosionEffect.SetPosition(skree->GetPosition().x, skree->GetPosition().y);
				explosionEffect.Play();
				//instantiate health item
				HealthItem *healthItem = new HealthItem();
				healthItem->Create(&world, &itemsTexture, skree->GetPosition().x, skree->GetPosition().y);
				healthItems.push_back(healthItem);
			}
			//delete skree
			delete skree;
			skree = NULL;
			skrees.erase(skrees.begin() + i);

		}
	}
	
	//update zoomers
	for (int i = 0; i < zoomers.size(); i++)
	{
		Zoomer* zoomer = zoomers[i];
		zoomer->Update(dt);
		if (zoomer->GetHealth() <= 0)
		{
			explosionEffect.SetSize(32, 32);
			explosionEffect.SetPosition(zoomer->GetPosition().x, zoomer->GetPosition().y);
			explosionEffect.Play();
			//instantiate health item
			HealthItem *healthItem = new HealthItem();
			healthItem->Create(&world, &itemsTexture, zoomer->GetPosition().x, zoomer->GetPosition().y);
			healthItems.push_back(healthItem);

			//delete skree
			delete zoomer;
			zoomer = NULL;
			zoomers.erase(zoomers.begin() + i);

		}
	}

	//update rios
	for (int i = 0; i < rios.size(); i++)
	{
		Rio* rio = rios[i];
		rio->Update(dt);
		if (rio->GetHealth() <= 0)
		{
			explosionEffect.SetSize(32, 32);
			explosionEffect.SetPosition(rio->GetPosition().x, rio->GetPosition().y);
			explosionEffect.Play();
			//instantiate health item
			HealthItem *healthItem = new HealthItem();
			healthItem->Create(&world, &itemsTexture, rio->GetPosition().x, rio->GetPosition().y);
			healthItems.push_back(healthItem);

			//delete skree
			delete rio;
			rio = NULL;
			rios.erase(rios.begin() + i);

		}
	}

	//update rippers
	for (int i = 0; i < rippers.size(); i++)
	{
		Ripper* ripper = rippers[i];
		ripper->Update(dt);
		if (ripper->GetHealth() <= 0)
		{
			explosionEffect.SetSize(32, 32);
			explosionEffect.SetPosition(ripper->GetPosition().x, ripper->GetPosition().y);
			explosionEffect.Play();
			//instantiate health item
			HealthItem *healthItem = new HealthItem();
			healthItem->Create(&world, &itemsTexture, ripper->GetPosition().x, ripper->GetPosition().y);
			healthItems.push_back(healthItem);

			//delete skree
			delete ripper;
			ripper = NULL;
			rippers.erase(rippers.begin() + i);

		}
	}

	

	//update kraid
	if (kraid!=NULL )
	{
		kraid->Update(dt);
		if (kraid->IsDead())
		{
			explosionEffect.SetSize(64, 64);
			explosionEffect.SetPosition(kraid->GetPosition().x, kraid->GetPosition().y);
			explosionEffect.Play();
			delete kraid;
			kraid = NULL;
		}
	}

	//mother brain
	if (motherBrain != NULL)
	{
		motherBrain->Update(dt);
		if (motherBrain->IsDead())
		{
			explosionEffect.SetSize(64, 64);
			explosionEffect.SetPosition(motherBrain->GetPosition().x, motherBrain->GetPosition().y);
			explosionEffect.Play();
			delete motherBrain;
			motherBrain = NULL;
		}

		//update cannons
		for (std::vector<Cannon*>::iterator it = cannons.begin(); it != cannons.end(); ++it)
		{
			(*it)->Update(dt);
		}
		//update circle cannons
		for (std::vector<CircleCannon*>::iterator it = circleCannons.begin(); it != circleCannons.end(); ++it)
		{
			(*it)->Update(dt);
		}

		//update healthPiles
		for (std::vector<HealthPile*>::iterator it = healthPiles.begin(); it != healthPiles.end(); ++it)
		{
			(*it)->Update(dt);
		}

	}




	//update effect
	explosionEffect.Update(dt);


	//update items
	maruMariItem.Update(dt);
	bombItem.Update(dt);

	for (int i =0; i< healthItems.size(); i++)
	{
		HealthItem* healthItem = healthItems[i];
		healthItem->Update(dt);
		if (healthItem->IsHitPlayer())
		{
			delete healthItem;
			healthItem = NULL;
			healthItems.erase(healthItems.begin() + i);
		}
	}
	

	//update camera
	if (player.GetPosition().y > cam.GetPosition().y + 150)
	{
		cam.SetPosition(cam.GetPosition().x, player.GetPosition().y - 150);
	}
	else
	{
		if (player.GetPosition().y < cam.GetPosition().y - 150)
		{
			cam.SetPosition(cam.GetPosition().x, player.GetPosition().y + 150);
		}
	}
	cam.SetPosition(player.GetPosition().x, cam.GetPosition().y);

	//update Label
	if (player.GetHealth() < 0)
	{
		playerHealthLabel.SetText(std::to_string(0));
	}
	else
	{
		playerHealthLabel.SetText(std::to_string(player.GetHealth()));
	}

	playerHealthLabel.SetPosition(cam.GetPosition().x - 250, cam.GetPosition().y + 200);


	//update doors
	for (std::vector<Door*>::iterator it = doors.begin(); it != doors.end(); ++it)
	{
		(*it)->Update(dt);
	}
	//RENDER
	Render();


	//play sound BrinstarTheme
	Sound::Loop(BrinstarTheme);

}

void PlayScene::Release()
{
	world.Release();
	player.Release();
	for (std::vector<Rio*>::iterator it = rios.begin(); it != rios.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}
	
	for (std::vector<Zoomer*>::iterator it = zoomers.begin(); it != zoomers.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}

	for (std::vector<Skree*>::iterator it = skrees.begin(); it != skrees.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}

	for (std::vector<HealthItem*>::iterator it = healthItems.begin(); it != healthItems.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}

	for (std::vector<BreakablePlatform*>::iterator it = breakablePlatforms.begin(); it != breakablePlatforms.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}

	for (std::vector<Cannon*>::iterator it = cannons.begin(); it != cannons.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}

	for (std::vector<HealthPile*>::iterator it = healthPiles.begin(); it != healthPiles.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}

	//update circle cannons
	for (std::vector<CircleCannon*>::iterator it = circleCannons.begin(); it != circleCannons.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}

	font.Release();
}

bool PlayScene::isOver()
{
	return this->player.IsDead();
}

CSound *PlayScene::GetSound()
{
	return this->BrinstarTheme;
}