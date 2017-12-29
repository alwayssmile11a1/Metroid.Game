#include "Cannon.h"



Cannon::Cannon()
{

}


Cannon::~Cannon()
{
}

void Cannon::Create(World *world, Texture *texture, Cannon::Type type, int randomIndex, int x, int y)
{
	isBulletDestroyed = true;
	this->world = world;
	lastShot = 0;

	TexturePacker p = TexturePacker(texture, "Resources/bosses_packer.xml");

	cannonAnimation.AddRegion(p.GetRegion("cannon"));
	cannonAnimation.SetIndex(randomIndex);
	bulletAnimation.AddRegion(p.GetRegion("cannonbullet"));
	bulletAnimation.SetIndex(randomIndex);

	SetRegion(*cannonAnimation.GetKeyAnimation());
	SetSize(25, 25);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(25, 25);
	body = world->CreateBody(bodyDef);
	body->categoryBits = CANNON_BIT;
	body->maskBits = PLAYER_BIT;
	body->PutExtra(this);


	//setup bullet
	BodyDef bulletDef;
	bulletDef.bodyType = Body::BodyType::Static;
	bulletDef.position.Set(x, y);
	bulletDef.size.Set(12, 12);
	bulletDef.isSensor = true;
	cannonBullet.body = world->CreateBody(bulletDef);
	cannonBullet.body->categoryBits = CANNON_BIT;
	cannonBullet.body->maskBits = PLAYER_BIT|PLATFORM_BIT;
	cannonBullet.body->PutExtra(this);

	cannonBullet.SetRegion(*bulletAnimation.GetKeyAnimation());
	cannonBullet.SetSize(12, 12);
	cannonBullet.SetPosition(x, y);

	switch (type)
	{
	case Cannon::Right:
		SetRotation(-180);
		cannonBullet.SetRotation(-180);
		break;
	case Cannon::Top:
		SetRotation(-90);
		cannonBullet.SetRotation(-90);
		break;
	default:
		break;
	}


	//effect
	Animation explosionAnimation;
	explosionAnimation.AddRegion(p.GetRegion("cannonbulletexplosion"));
	bulletExplosionEffect = Effect(explosionAnimation);
	bulletExplosionEffect.SetLiveTime(0.3);
	bulletExplosionEffect.SetSize(15, 15);
	
}

void Cannon::Create(World *world, Texture *texture, Cannon::Type type, int randomIndex, Body* body)
{
	isBulletDestroyed = true;
	this->world = world;
	lastShot = 0;

	TexturePacker p = TexturePacker(texture, "Resources/bosses_packer.xml");

	cannonAnimation.AddRegion(p.GetRegion("cannon"));
	cannonAnimation.SetIndex(randomIndex);
	bulletAnimation.AddRegion(p.GetRegion("cannonbullet"));
	bulletAnimation.SetIndex(randomIndex);

	SetRegion(*cannonAnimation.GetKeyAnimation());
	SetSize(25, 25);
	SetPosition(body->GetPosition().x, body->GetPosition().y);

	//setup body
	this->body = body;
	body->SetBodyType(Body::BodyType::Static);
	body->SetSize(25, 25);
	body->categoryBits = CANNON_BIT;
	body->maskBits = PLAYER_BIT;
	body->PutExtra(this);


	//setup bullet
	BodyDef bulletDef;
	bulletDef.bodyType = Body::BodyType::Static;
	bulletDef.position.Set(body->GetPosition().x, body->GetPosition().y);
	bulletDef.size.Set(12, 12);
	bulletDef.isSensor = true;
	cannonBullet.body = world->CreateBody(bulletDef);
	cannonBullet.body->categoryBits = CANNON_BIT;
	cannonBullet.body->maskBits = PLAYER_BIT | PLATFORM_BIT;
	cannonBullet.body->PutExtra(this);

	cannonBullet.SetRegion(*bulletAnimation.GetKeyAnimation());
	cannonBullet.SetSize(12, 12);
	cannonBullet.SetPosition(body->GetPosition().x, body->GetPosition().y);

	switch (type)
	{
	case Cannon::Right:
		SetRotation(-180);
		cannonBullet.SetRotation(-180);
		break;
	case Cannon::Top:
		SetRotation(-90);
		cannonBullet.SetRotation(-90);
		break;
	default:
		break;
	}


	//effect
	Animation explosionAnimation;
	explosionAnimation.AddRegion(p.GetRegion("cannonbulletexplosion"));
	bulletExplosionEffect = Effect(explosionAnimation);
	bulletExplosionEffect.SetLiveTime(0.3);
	bulletExplosionEffect.SetSize(15, 15);
}

void Cannon::Render(SpriteBatch *batch)
{
	if (!isBulletDestroyed)
	{
		batch->Draw(cannonBullet);
	}

	batch->Draw(*this);

	bulletExplosionEffect.Render(batch);
}

void Cannon::Update(float dt)
{
	float currentTime = GetTickCount() / 1000.0f;
	if (currentTime > CANNOTFIRERATE + lastShot) //don't shoot more if we have just shooted 
	{
		lastShot = currentTime;
		SetRegion(*cannonAnimation.Next(dt));
		cannonBullet.SetRegion(*bulletAnimation.Next(dt));

		if (isBulletDestroyed) //shoot if bullet is destroyed
		{
			isBulletDestroyed = false;
			cannonBullet.body->SetBodyType(Body::BodyType::Kinematic);

			int angleOffset;
			if (cannonAnimation.GetIndex() >= 5)
			{
				angleOffset = 8 - cannonAnimation.GetIndex();
			}
			else
			{
				angleOffset = cannonAnimation.GetIndex();
			}

			cannonBullet.body->SetVelocity(-7 * sin(45 * angleOffset* Pi / 180 + this->GetRotation()*Pi/180),
										   -7 * cos(45 * angleOffset* Pi / 180 + this->GetRotation()*Pi/180));

			cannonBullet.body->SetPosition(this->GetPosition().x,this->GetPosition().y);

		}

	}


	cannonBullet.SetPosition(cannonBullet.body->GetPosition().x, cannonBullet.body->GetPosition().y);
	bulletExplosionEffect.Update(dt);
}


void Cannon::OnHitGround()
{
	isBulletDestroyed = true;
	cannonBullet.body->SetBodyType(Body::BodyType::Static);
	bulletExplosionEffect.SetPosition(cannonBullet.body->GetPosition().x, cannonBullet.body->GetPosition().y);
	bulletExplosionEffect.Play();
}


