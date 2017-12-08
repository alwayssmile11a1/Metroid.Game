#include "Skree.h"



Skree::Skree()
{
	
}


Skree::~Skree()
{
}

void Skree::Create(World *world, Texture *skreeTexture, int x, int y)
{
	this->world = world;

	TexturePacker p = TexturePacker(skreeTexture, "Resources/enemies_packer.xml");

	skreeAnimation.AddRegion(p.GetRegion("skree"));
	skreeAnimation.SetFrameInterval(0.04);

	skreeBulletAnimation.AddRegion(p.GetRegion("skreebullet"));
	

	SetRegion(skreeAnimation.GetKeyAnimation());
	SetSize(16, 33);
	SetPosition(x, y);
	
	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(16, 33);
	body = world->CreateBody(bodyDef);
	body->categoryBits = SKREE_BIT;
	body->maskBits = PLAYER_BIT|PLATFORM_BIT|BULLET_BIT;
	body->PutExtra(this);

}


void Skree::HandlePhysics()
{
	
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
	
	//set sprite position
	this->SetPosition(body->GetPosition().x, body->GetPosition().y);
	

	SetRegion(skreeAnimation.Next(dt));
	
	if (isDead)
	{
		stateTime += dt;
		body->SetBodyType ( Body::BodyType::Static);

		if (stateTime > SKREELIVETIME)
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
				skreeBullet.body = world->CreateBody(bodyDef);
				skreeBullet.body->SetVelocity(3 * cos(45 * i*PI / 180), 3 * sin(45 * i*Pi / 180));
				skreeBullet.body->categoryBits = SKREE_BIT;
				skreeBullet.body->maskBits = PLAYER_BIT | PLATFORM_BIT | BULLET_BIT;
				//sprite
				skreeBullet.sprite.SetRegion(skreeBulletAnimation.GetKeyAnimation());
				skreeBullet.sprite.SetSize(6, 7);
				skreeBullet.sprite.SetPosition(body->GetPosition().x, body->GetPosition().y);

				skreeBullets.push_back(skreeBullet);
			}
			world->DestroyBody(body);
			isDead = false;
		}

	}

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

void Skree::Follow(Player *player)
{
	if (player->GetPosition().x - body->GetPosition().x > 0)
	{
		body->SetVelocity(1.5f, body->GetVelocity().y);
	}
	else
	{
		body->SetVelocity(-1.5f, body->GetVelocity().y);
	}
}

void Skree::OnHitGround()
{
	isDead = true;
}

void Skree::OnHitPlayer()
{
	body->SetBodyType(Body::BodyType::Dynamic);
}
