#include "Kraid.h"



Kraid::Kraid()
{

}


Kraid::~Kraid()
{
}

void Kraid::Create(World *world, Texture *texture,Player*player, int x, int y)
{
	this->player = player;
	health = 20;
	stateTime = -1;
	bulletStateTime = -1;

	TexturePacker p = TexturePacker(texture, "Resources/bosses_packer.xml");

	animation.AddRegion(p.GetRegion("kraid"));
	animation.SetFrameInterval(0.2);


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
	body->maskBits = PLAYER_BIT | BULLET_BIT | EXPLOSION_BIT|PLATFORM_BIT;
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
		bullet.body->PutExtra(this);
		bullets.push_back(bullet);
	}


}

void Kraid::HandlePhysics()
{
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
	//render bullets
	for (std::vector<KraidBullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
	{

		it->SetPosition(it->body->GetPosition().x, it->body->GetPosition().y);
		batch->Draw(*it);
	}

	batch->Draw(*this);
}

void Kraid::Update(float dt)
{
	SetRegion(*animation.Next(dt));


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

	//float currentTime = GetTickCount() / 1000.0f;
	//if (currentTime > FIRERATE + lastShot) //don't shoot more if we have just shooted 
	//{

	//	lastShot = currentTime;
	//	bulletStateTime = 0;

	//}

	if (bulletStateTime >= 0)
	{
		bulletStateTime += dt;
	}

	if (bulletStateTime > KRAIDBULLETLIVETIME)
	{
		bulletStateTime = -1;
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
				it->body->SetVelocity(3, 0);
			}
			else
			{
				it->body->SetPosition(this->GetPosition().x - this->GetSize().x / 2 - it->GetSize().x / 2 + i * 5, this->GetPosition().y + i * 20);
				it->Flip(false, false);
				it->body->SetVelocity(-3, 0);
			}
			i++;
		}

		bulletStateTime += dt;
	}
}


void Kraid::OnHitBullet()
{
	health--;
}

void Kraid::OnHitBomb()
{
	health -= 3;
}

bool Kraid::IsDead()
{
	return health <= 0;
}
