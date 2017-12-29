#include "Kraid.h"



Kraid::Kraid()
{

}


Kraid::~Kraid()
{
}

void Kraid::Create(World *world, Texture *texture,Player*player, int x, int y)
{
	this->world = world;
	this->player = player;
	health = 20;
	stateTime = -1;
	bulletStateTime = -1;
	boomerangStateTime = -0.5;
	hitBulletTime = -1;

	TexturePacker p = TexturePacker(texture, "Resources/bosses_packer.xml");

	animation.AddRegion(p.GetRegion("kraid"));
	animation.SetFrameInterval(0.2);

	behingHitAnimation.AddRegion(p.GetRegion("beinghitkraid"));
	behingHitAnimation.SetFrameInterval(0.2);

	SetRegion(*animation.GetKeyAnimation());
	SetSize(48, 64);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(48, 64);
	body = world->CreateBody(bodyDef);
	body->categoryBits = KRAID_BIT;
	body->maskBits = BULLET_BIT | EXPLOSION_BIT|PLATFORM_BIT;
	body->PutExtra(this);



	//setup bullets
	TextureRegion bulletRegion = p.GetRegion("kraidbullet").front();
	for (int i = 0; i < 3; i++)
	{
		KraidBullet bullet;
		bullet.SetRegion(bulletRegion);
		bullet.SetSize(16, 6);
		//setup body
		BodyDef bulletDef;
		bulletDef.bodyType = Body::BodyType::Kinematic;
		bulletDef.position.Set(x, y);
		bulletDef.size.Set(16, 6);
		bulletDef.isSensor = true;
		bullet.body = world->CreateBody(bulletDef);
		bullet.body->categoryBits = KRAID_BIT;
		bullet.body->maskBits = PLAYER_BIT;
		bullet.body->SetID("bullet");
		bullet.body->PutExtra(this);
		bullets.push_back(bullet);
	}


	//setup boomerang
	boomerangAnimation.AddRegion(p.GetRegion("kraidboomerang"));
	boomerangAnimation.SetFrameInterval(0.02);
	for (int i = 0; i < 2; i++)
	{
		KraidBullet boomerang;
		boomerang.SetRegion(*boomerangAnimation.GetKeyAnimation());
		boomerang.SetSize(16, 14);
		//setup body
		BodyDef boomerangDef;
		boomerangDef.bodyType = Body::BodyType::Dynamic;
		boomerangDef.position.Set(x, y);
		boomerangDef.size.Set(16, 14);
		boomerangDef.isSensor = true;
		boomerang.body = world->CreateBody(boomerangDef);
		boomerang.body->categoryBits = KRAID_BIT;
		boomerang.body->maskBits = PLAYER_BIT;
		boomerang.body->SetMass(2);
		boomerang.body->SetLinearDrag(0.5, 1);
		boomerang.body->SetID("boomerang");
		boomerang.body->PutExtra(this);
		boomerangs.push_back(boomerang);
	}

}

void Kraid::Create(World *world, Texture *texture, Player*player, Body* body)
{
	this->world = world;
	this->player = player;
	health = 20;
	stateTime = -1;
	bulletStateTime = -1;
	boomerangStateTime = -0.5;
	hitBulletTime = -1;

	TexturePacker p = TexturePacker(texture, "Resources/bosses_packer.xml");

	animation.AddRegion(p.GetRegion("kraid"));
	animation.SetFrameInterval(0.2);

	behingHitAnimation.AddRegion(p.GetRegion("beinghitkraid"));
	behingHitAnimation.SetFrameInterval(0.2);

	SetRegion(*animation.GetKeyAnimation());
	SetSize(48, 64);
	SetPosition(body->GetPosition().x, body->GetPosition().y);

	//setup body
	this->body = body;
	body->SetBodyType(Body::BodyType::Kinematic);
	body->SetSize(48, 64);
	body->categoryBits = KRAID_BIT;
	body->maskBits = BULLET_BIT | EXPLOSION_BIT | PLATFORM_BIT;
	body->PutExtra(this);



	//setup bullets
	TextureRegion bulletRegion = p.GetRegion("kraidbullet").front();
	for (int i = 0; i < 3; i++)
	{
		KraidBullet bullet;
		bullet.SetRegion(bulletRegion);
		bullet.SetSize(16, 6);
		//setup body
		BodyDef bulletDef;
		bulletDef.bodyType = Body::BodyType::Kinematic;
		bulletDef.position.Set(body->GetPosition().x, body->GetPosition().y);
		bulletDef.size.Set(16, 6);
		bulletDef.isSensor = true;
		bullet.body = world->CreateBody(bulletDef);
		bullet.body->categoryBits = KRAID_BIT;
		bullet.body->maskBits = PLAYER_BIT;
		bullet.body->SetID("bullet");
		bullet.body->PutExtra(this);
		bullets.push_back(bullet);
	}


	//setup boomerang
	boomerangAnimation.AddRegion(p.GetRegion("kraidboomerang"));
	boomerangAnimation.SetFrameInterval(0.02);
	for (int i = 0; i < 2; i++)
	{
		KraidBullet boomerang;
		boomerang.SetRegion(*boomerangAnimation.GetKeyAnimation());
		boomerang.SetSize(16, 14);
		//setup body
		BodyDef boomerangDef;
		boomerangDef.bodyType = Body::BodyType::Dynamic;
		boomerangDef.position.Set(body->GetPosition().x, body->GetPosition().y);
		boomerangDef.size.Set(16, 14);
		boomerangDef.isSensor = true;
		boomerang.body = world->CreateBody(boomerangDef);
		boomerang.body->categoryBits = KRAID_BIT;
		boomerang.body->maskBits = PLAYER_BIT;
		boomerang.body->SetMass(2);
		boomerang.body->SetLinearDrag(0.5, 1);
		boomerang.body->SetID("boomerang");
		boomerang.body->PutExtra(this);
		boomerangs.push_back(boomerang);
	}

}


void Kraid::HandlePhysics()
{
	if (body == NULL) return;

	if (player->GetPosition().x > this->GetPosition().x)
	{
		//if (bulletStateTime == 0)
		//{
		//	//update bullets
		//	for (std::vector<KraidBullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
		//	{
		//		it->Flip(true, false);
		//		it->body->SetVelocity(3, 0);

		//	}
		//}

		if (this->IsFlipX())
		{
			float randomX = (rand() % 200) / 100.0f - 0.3f;
			body->SetVelocity(randomX, 0);
		}
	}
	else
	{
		//if (bulletStateTime == 0)
		//{
		//	//update bullets
		//	for (std::vector<KraidBullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
		//	{
		//		it->Flip(false, false);
		//		it->body->SetVelocity(-3, 0);
		//	}
		//}

		if (player->GetPosition().x < this->GetPosition().x )
		{
			if (!this->IsFlipX())
			{
				float randomX = -(rand() % 200) / 100.0f + 0.3f;
				body->SetVelocity(randomX, 0);
			}
		}
	}
}


void Kraid::Render(SpriteBatch *batch)
{
	if (body == NULL) return;

	//render bullets
	for (std::vector<KraidBullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
	{

		it->SetPosition(it->body->GetPosition().x, it->body->GetPosition().y);
		batch->Draw(*it);
	}

	batch->Draw(*this);

	//render boomerangs
	for (std::vector<KraidBullet>::iterator it = boomerangs.begin(); it != boomerangs.end(); it++)
	{
		it->SetRegion(*boomerangAnimation.GetKeyAnimation());
		it->SetPosition(it->body->GetPosition().x, it->body->GetPosition().y);
		batch->Draw(*it);
	}
}

void Kraid::Update(float dt)
{
	if (body == NULL) return;


	if (health <= 0)
	{
		world->DestroyBody(body);
		body = NULL;

		//destroy bullets
		for (std::vector<KraidBullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
		{
			world->DestroyBody(it->body);
		
		}

		//destroy boomerangs
		for (std::vector<KraidBullet>::iterator it = boomerangs.begin(); it != boomerangs.end(); it++)
		{
			world->DestroyBody(it->body);
		}
		health = -100;
		return;
	}

	if (hitBulletTime == -1) //not being hit by any bullet
	{
		SetRegion(*animation.Next(dt));
	}
	else
	{
		SetRegion(*behingHitAnimation.Next(dt));

		hitBulletTime += 0.02;
		if (hitBulletTime > MAXHITBULLETTIME)
		{
			hitBulletTime = -1; 
		}
	}


	if (player->GetPosition().x > this->GetPosition().x && !this->IsFlipX() && stateTime == -1)
	{
		stateTime = 0; //start flipping
	}

	if (player->GetPosition().x < this->GetPosition().x && this->IsFlipX() && stateTime == -1)
	{
		stateTime = 0; //start flipping
	}

	if (stateTime >= 0)
	{
		stateTime += dt;
	}

	if (stateTime > TURNINGDELAYTIME) //flip after delaytime
	{
		if (player->GetPosition().x > this->GetPosition().x)
		{
			Flip(true, false);
		}
		else
		{
			Flip(false, false);
		}

		stateTime = -1;
	}

	SetPosition(body->GetPosition().x, body->GetPosition().y);


	if (bulletStateTime >= 0)
	{
		bulletStateTime += dt;
		
	}

	if (boomerangStateTime >= 0)
	{
		boomerangStateTime += dt;
		boomerangAnimation.Next(dt);
	}

	if (bulletStateTime > KRAIDBULLETLIVETIME)
	{
		bulletStateTime = -1;
	}

	if (boomerangStateTime > KRAIDBOOMERANGLIVETIME)
	{
		boomerangStateTime = -0.5;
	}


	if (bulletStateTime < 0)
	{
		//update bullet
		int i = -1;
		for (std::vector<KraidBullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
		{
			if (player->GetPosition().x > this->GetPosition().x)
			{
				it->body->SetPosition(this->GetPosition().x + this->GetSize().x / 2 + it->GetSize().x / 2 - i * 5, this->GetPosition().y + i * 20);
				it->Flip(true, false);
				it->body->SetVelocity(5, 0);
			}
			else
			{
				it->body->SetPosition(this->GetPosition().x - this->GetSize().x / 2 - it->GetSize().x / 2 + i * 5, this->GetPosition().y + i * 20);
				it->Flip(false, false);
				it->body->SetVelocity(-5, 0);
			}
			i++;
		}


		bulletStateTime += dt;
	}

	if (boomerangStateTime < 0)
	{
		int i = 0;
		//update boomerang
		for (std::vector<KraidBullet>::iterator it = boomerangs.begin(); it != boomerangs.end(); it++)
		{
			if (player->GetPosition().x > this->GetPosition().x)
			{
				it->body->SetVelocity(rand() % 5 + 4, rand() % 6 + 4);
			}
			else
			{
				it->body->SetVelocity(-(rand() % 5 + 4), rand() % 6 + 4);
			}

			if (!this->IsFlipX())
			{
				it->body->SetPosition(this->GetPosition().x + this->GetSize().x / 2, this->GetPosition().y + this->GetSize().y / 2 - i * 10);
			}
			else
			{
				it->body->SetPosition(this->GetPosition().x - this->GetSize().x / 2, this->GetPosition().y + this->GetSize().y / 2 - i * 10);
			}

			i++;
		}

		boomerangStateTime += dt;
	}





}


void Kraid::OnHitBullet()
{
	if (hitBulletTime != -1) return;
	health--;
	hitBulletTime = 0;
}

void Kraid::OnHitBomb()
{
	if (hitBulletTime != -1) return;
	health -= 3;
	hitBulletTime = 0;
}

bool Kraid::IsDead()
{
	return health <= 0;
}
