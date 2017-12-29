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
	hitBulletTime = -1;
	health = 2;

	this->world = world;

	TexturePacker p = TexturePacker(skreeTexture, "Resources/enemies_packer.xml");

	skreeAnimation.AddRegion(p.GetRegion("skree"));
	skreeAnimation.SetFrameInterval(0.04);

	skreeHitAnimation.AddRegion(p.GetRegion("skreehit"));
	skreeHitAnimation.SetFrameInterval(0.04);

	skreeBulletAnimation.AddRegion(p.GetRegion("skreebullet"));
	

	SetRegion(*skreeAnimation.GetKeyAnimation());
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
	body->maskBits = PLAYER_BIT|PLATFORM_BIT|BULLET_BIT|EXPLOSION_BIT;
	body->PutExtra(this);

}


void Skree::HandlePhysics(Player* player)
{
	if (stateTime > 0||isDead || hitBulletTime!=-1) return;

	if (this->GetPosition().y - player->GetPosition().y < 500 && this->GetPosition().y > player->GetPosition().y) //if player and skree is too far apart each other, don't do anything 
	{
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


}

void Skree::Render(SpriteBatch *batch)
{
	if (isDead) return;

	if (stateTime > SKREEBULLETLIVETIME) return;

	if (stateTime < SKREELIVETIMEAFTERGROUND)
	{
		batch->Draw(*this);
	}

	for (std::vector<SkreeBullet>::iterator bullet = skreeBullets.begin(); bullet != skreeBullets.end(); ++bullet)
	{
		bullet->sprite.SetPosition(bullet->body->GetPosition().x, bullet->body->GetPosition().y);
		batch->Draw(bullet->sprite);
	}
}

void Skree::Update(float dt)
{
	if (isDead) return;

	if (health <= 0)
	{
		isDead = true;
		world->DestroyBody(body);
		return;
	}


	if (body != NULL)
	{
		//set sprite position
		this->SetPosition(body->GetPosition().x, body->GetPosition().y);
	}
	
	if (hitBulletTime==-1) //-1 means not being hit by bullet
	{
		SetRegion(*skreeAnimation.Next(dt));
	}
	else
	{
		if (hitBulletTime < MAXHITBULLETTIME)
		{
			SetRegion(*skreeHitAnimation.Next(dt));
			hitBulletTime += dt;
		}
		else
		{
			hitBulletTime = -1;
			body->SetBodyType(Body::BodyType::Dynamic);
		}
	}
	
	if (!isDead )
	{
		if (isHitGround) //hit ground -> fire some bullets
		{
			stateTime += dt;
			body->SetBodyType(Body::BodyType::Static);

			if (stateTime > SKREELIVETIMEAFTERGROUND)
			{
				//instantiate bullets
				for (int i = 0; i < 5; i++)
				{
					//5 skree bullets fired when skree hits ground
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
					skreeBullet.sprite.SetRegion(*skreeBulletAnimation.GetKeyAnimation());
					skreeBullet.sprite.SetSize(6, 7);
					skreeBullet.sprite.SetPosition(body->GetPosition().x, body->GetPosition().y);

					skreeBullets.push_back(skreeBullet);

				}

				world->DestroyBody(body);
				body = NULL;
				isHitGround = false; //set this to not instantiate more bullets
			}
		}
	}

	//update skree bullets
	if (stateTime > SKREELIVETIMEAFTERGROUND)
	{
		stateTime += dt;
		if (stateTime > SKREEBULLETLIVETIME)
		{
			for (std::vector<SkreeBullet>::iterator bullet = skreeBullets.begin(); bullet != skreeBullets.end(); ++bullet)
			{
				world->DestroyBody(bullet->body);
			}
			skreeBullets.clear();

			isDead = true;
		}
	}


}


void Skree::OnHitGround()
{
	isHitGround = true;
}


void Skree::OnHitBullet()
{
	if (hitBulletTime != -1) return;
	health --;
	hitBulletTime = 0;
	//stop this body a little bit 
	body->SetVelocity(0, 0);
}

void Skree::OnHitBomb()
{
	health = 0;
	hitBulletTime = 0;
	//stop this body a little bit 
	body->SetVelocity(0, 0);
}

bool Skree::IsDead()
{
	return isDead;
}

int Skree::GetHealth()
{
	return health;
}