#include "Bullet.h"



Bullet::Bullet()
{
}


Bullet::~Bullet()
{

}

Bullet::Bullet(World *world, Texture* texture)
{
	isDestroyed = false;
	stateTime = 0;

	//get bullet 
	TexturePacker p = TexturePacker(texture, "Resources/samusaran_packer.xml");
	SetRegion(p.GetRegion("bullet").front());

	this->world = world;
	SetSize(6,7);

	//body definition
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.size.Set(6,7);

	//create body
	mainBody = world->CreateBody(bodyDef);
	mainBody->categoryBits = BULLET_BIT;
	mainBody->maskBits = SKREE_BIT|ZOOMER_BIT|RIO_BIT|MOTHERBRAIN_BIT;
	mainBody->PutExtra(this);
	
}

void Bullet::Render(SpriteBatch *batch)
{
	batch->Draw(*this);

}

void Bullet::Update(float dt)
{
	if (mainBody == NULL) return;
	//mainBody.SetPosition(mainBody.GetPosition().x+10, mainBody.GetPosition().y);
	SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y);
	stateTime += dt;
	if (stateTime > BULLETLIVETIME)
	{
		world->DestroyBody(mainBody);
		mainBody = NULL;
		isDestroyed = true;
	}
}

float Bullet::GetBulletSpeed()
{
	return BULLETSPEED;
}

Body* Bullet::GetMainBody()
{
	return mainBody;
}

bool Bullet::IsDestroyed()
{
	return isDestroyed;
}

void Bullet::OnHitEnemy()
{
	stateTime = 100; //force to be dead
}



