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
	liveTime = LIVETIME;
	bulletSpeed = BULLETSPEED;

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
	world->AddBody(&mainBody);
	SetMainBody(&mainBody);
	
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
	if (stateTime > liveTime)
	{
		world->RemoveBody(&mainBody);
		isDestroyed = true;
	}
}

float Bullet::GetBulletSpeed()
{
	return bulletSpeed;
}

bool Bullet::IsDestroyed()
{
	return isDestroyed;
}

//void Bullet::Release()
//{
//	
//}

