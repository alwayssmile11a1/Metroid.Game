#include "Skree.h"



Skree::Skree()
{
	
}


Skree::~Skree()
{
}

void Skree::Create(World *world, Texture *skreeTexture, int x, int y)
{
	stateTime = 0;
	hitBulletTime = 100;
	health = 2;

	this->world = world;

	TexturePacker p = TexturePacker(skreeTexture, "Resources/enemies_packer.xml");

	skreeAnimation.AddRegion(p.GetRegion("skree"));
	skreeAnimation.SetFrameInterval(0.04);

	skreeHitAnimation.AddRegion(p.GetRegion("skreehit"));
	skreeHitAnimation.SetFrameInterval(0.04);

	skreeBulletAnimation.AddRegion(p.GetRegion("skreebullet"));
	

	SetRegion(skreeAnimation.GetKeyAnimation());
	SetSize(16, 33);
	SetPosition(x, y);
	
	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(16, 33);
	bodyDef.isSensor = true;
	body = world->CreateBody(bodyDef);
	body->categoryBits = SKREE_BIT;
	body->maskBits = PLAYER_BIT|PLATFORM_BIT|BULLET_BIT;
	body->PutExtra(this);

}


void Skree::HandlePhysics(Player* player)
{
	if (isDead||hitBulletTime!=100) return;
	if (abs(player->GetPosition().x - this->GetPosition().x) < 100)
	{
		body->SetBodyType(Body::BodyType::Dynamic);
		if (player->GetPosition().x - body->GetPosition().x > 0)
		{
			body->SetVelocity(2, -4);
		}
		else
		{
			body->SetVelocity(-2, -4);
		}
	}

}

void Skree::Render(SpriteBatch *batch)
{
	if (stateTime > SKREEBULLETLIVETIME) return;

	if (stateTime < SKREELIVETIME)
	{
		batch->Draw(*this);
	}
	for (std::vector<SkreeBullet>::iterator bullet = skreeBullets.begin(); bullet != skreeBullets.end(); ++bullet)
	{
		(*bullet).sprite.SetPosition((*bullet).body->GetPosition().x, (*bullet).body->GetPosition().y);
		batch->Draw((*bullet).sprite);
	}
}

void Skree::Update(float dt)
{
	if (health == 0)
	{
		isDead = true;
	}

	//set sprite position
	this->SetPosition(body->GetPosition().x, body->GetPosition().y);
	
	if (hitBulletTime==100) //100 means not being hit by bullet
	{
		SetRegion(skreeAnimation.Next(dt));
	}
	else
	{
		if (hitBulletTime < MAXHITBULLETTIME)
		{
			SetRegion(skreeHitAnimation.Next(dt));
			hitBulletTime += dt;
		}
		else
		{
			hitBulletTime = 100;
			body->SetBodyType(Body::BodyType::Dynamic);
		}
	}
	
	if (isDead)
	{
		stateTime += dt;
		body->SetBodyType ( Body::BodyType::Static);

		if (stateTime > SKREELIVETIME)
		{
			if (health > 0) //instantiate skree bullet only if there is still some health left
			{
				for (int i = 0; i < 5; i++)
				{
					//4 skree bullets fired when skree hits ground
					SkreeBullet skreeBullet;

					//create body
					BodyDef bodyDef;
					bodyDef.bodyType = Body::BodyType::Kinematic;
					bodyDef.position = body->GetPosition();
					bodyDef.size.Set(6, 7);
					bodyDef.isSensor = true;
					skreeBullet.body = world->CreateBody(bodyDef);
					skreeBullet.body->SetVelocity(3 * cos(45 * i*PI / 180), 3 * sin(45 * i*Pi / 180));
					skreeBullet.body->categoryBits = SKREE_BIT;
					skreeBullet.body->maskBits = PLAYER_BIT;
					//sprite
					skreeBullet.sprite.SetRegion(skreeBulletAnimation.GetKeyAnimation());
					skreeBullet.sprite.SetSize(6, 7);
					skreeBullet.sprite.SetPosition(body->GetPosition().x, body->GetPosition().y);

					skreeBullets.push_back(skreeBullet);
				}
			}

			world->DestroyBody(body);
			isDead = false; //set this because we don't want to go into the if statement anymore
		}

	}

	//skree bullet
	if (stateTime > SKREELIVETIME)
	{
		stateTime += dt;
		if (stateTime > SKREEBULLETLIVETIME)
		{
			for (std::vector<SkreeBullet>::iterator bullet = skreeBullets.begin(); bullet != skreeBullets.end(); ++bullet)
			{
				world->DestroyBody((*bullet).body);
			}
			skreeBullets.clear();
		}
	}


}


void Skree::OnHitGround()
{
	isDead = true;
}


void Skree::OnHitBullet()
{
	if (hitBulletTime != 100) return;
	health --;
	hitBulletTime = 0;
	//stop this body a little bit 
	body->SetBodyType(Body::BodyType::Static);
}

bool Skree::IsDead()
{
	return isDead;
}