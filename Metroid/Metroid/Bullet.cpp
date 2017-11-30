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

	this->world = world;
	SetTexture(texture);
	SetRectSize(6,7);
	SetRectPosition(250,9);
	SetSize(6,7);
	SetPosition(16 * 8, 16 * 12);

	//body
	mainBody.SetBodyType(Body::BodyType::Kinematic);
	mainBody.SetID("Bullet");
	mainBody.IsSensor(true);
	mainBody.SetSize(6,7);
	mainBody.SetPosition(16 * 8, 16 * 12);
	mainBody.categoryBits = BULLET_BIT;
	world->AddBody(&mainBody);
	
}

void Bullet::Render(SpriteBatch &batch)
{
	batch.Draw(*this);
}

void Bullet::Update(float dt)
{
	//mainBody.SetPosition(mainBody.GetPosition().x+10, mainBody.GetPosition().y);
	SetPosition(mainBody.GetPosition().x, mainBody.GetPosition().y);
	stateTime += dt;
	if (stateTime > LIVETIME)
	{
		world->RemoveBody(&mainBody);
		isDestroyed = true;
	}
}

float Bullet::GetBulletSpeed()
{
	return BULLETSPEED;
}

Body* Bullet::GetMainBody()
{
	return &mainBody;
}

bool Bullet::IsDestroyed()
{
	return isDestroyed;
}

//void Bullet::Release()
//{
//	
//}

