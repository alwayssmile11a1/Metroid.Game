#include "MotherBrainBullet.h"



MotherBrainBullet::MotherBrainBullet()
{
}


MotherBrainBullet::~MotherBrainBullet()
{

}

MotherBrainBullet::MotherBrainBullet(World *world, Texture* texture)
{
	isDestroyed = false;
	stateTime = 0;

	//get bullet 
	TexturePacker p = TexturePacker(texture, "Resources/samusaran_packer.xml");
	SetRegion(p.GetRegion("bullet").front());

	this->world = world;
	SetSize(6, 7);

	//body definition
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.size.Set(6, 7);

	//create body
	mainBody = world->CreateBody(bodyDef);
	mainBody->categoryBits = BULLET_BIT;
	mainBody->maskBits = SKREE_BIT | ZOOMER_BIT | RIO_BIT | MOTHERBRAIN_BIT;
	mainBody->PutExtra(this);

}

void MotherBrainBullet::Render(SpriteBatch *batch)
{
	batch->Draw(*this);

}

void MotherBrainBullet::Update(float dt)
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

float MotherBrainBullet::GetBulletSpeed()
{
	return BULLETSPEED;
}

Body* MotherBrainBullet::GetMainBody()
{
	return mainBody;
}

bool MotherBrainBullet::IsDestroyed()
{
	return isDestroyed;
}

void MotherBrainBullet::OnHitEnemy()
{
	stateTime = 100; //force to be dead
}



