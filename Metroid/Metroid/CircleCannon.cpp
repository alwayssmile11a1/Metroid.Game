#include "CircleCannon.h"



CircleCannon::CircleCannon()
{

}


CircleCannon::~CircleCannon()
{
}

void CircleCannon::Create(World *world, Texture *texture,Player* player, int x, int y)
{
	isBulletDestroyed = true;
	this->world = world;
	lastShot = 0;
	stateTime = -1;
	this->player = player;

	TexturePacker p = TexturePacker(texture, "Resources/enemies_packer.xml");

	bulletAnimation.AddRegion(p.GetRegion("circlecannon"));
	bulletAnimation.SetFrameInterval(0.05f);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(32, 32);
	body = world->CreateBody(bodyDef);
	body->categoryBits = PLATFORM_BIT;
	body->maskBits = PLAYER_BIT|FOOT_BIT|CANNON_BIT;
	body->PutExtra(this);


	//setup bullet
	BodyDef bulletDef;
	bulletDef.bodyType = Body::BodyType::Static;
	bulletDef.position.Set(x, y);
	bulletDef.size.Set(20, 20);
	bulletDef.isSensor = true;
	cannonBullet.body = world->CreateBody(bulletDef);
	cannonBullet.body->categoryBits = CIRCLECANNON_BIT;
	cannonBullet.body->maskBits = PLAYER_BIT;
	cannonBullet.body->PutExtra(this);

	cannonBullet.SetRegion(*bulletAnimation.GetKeyAnimation());
	cannonBullet.SetSize(20, 20);
	cannonBullet.SetPosition(x, y);



}

void CircleCannon::Create(World *world, Texture *texture, Player* player, Body* body)
{
	isBulletDestroyed = true;
	this->world = world;
	lastShot = 0;
	stateTime = -1;
	this->player = player;

	TexturePacker p = TexturePacker(texture, "Resources/enemies_packer.xml");

	bulletAnimation.AddRegion(p.GetRegion("circlecannon"));
	bulletAnimation.SetFrameInterval(0.05f);

	//setup body
	this->body = body;
	body->SetBodyType(Body::BodyType::Static);
	body->SetSize(32, 32);
	body->categoryBits = PLATFORM_BIT;
	body->maskBits = PLAYER_BIT | FOOT_BIT | CANNON_BIT;
	body->PutExtra(this);


	//setup bullet
	BodyDef bulletDef;
	bulletDef.bodyType = Body::BodyType::Static;
	bulletDef.position.Set(body->GetPosition().x, body->GetPosition().y);
	bulletDef.size.Set(20, 20);
	bulletDef.isSensor = true;
	cannonBullet.body = world->CreateBody(bulletDef);
	cannonBullet.body->categoryBits = CIRCLECANNON_BIT;
	cannonBullet.body->maskBits = PLAYER_BIT;
	cannonBullet.body->PutExtra(this);

	cannonBullet.SetRegion(*bulletAnimation.GetKeyAnimation());
	cannonBullet.SetSize(20, 20);
	cannonBullet.SetPosition(body->GetPosition().x, body->GetPosition().y);



}

void CircleCannon::HandlePhysics()
{

}

void CircleCannon::Render(SpriteBatch *batch)
{
	if (!isBulletDestroyed)
	{
		batch->Draw(cannonBullet);
	}

}

void CircleCannon::Update(float dt)
{
	cannonBullet.SetRegion(*bulletAnimation.Next(dt));
	float currentTime = GetTickCount() / 1000.0f;
	if (currentTime > CANNOTFIRERATE + lastShot) //don't shoot more if we have just shooted 
	{
		lastShot = currentTime;

		if (isBulletDestroyed) //shoot if bullet is destroyed
		{
			stateTime = 0;
			isBulletDestroyed = false;
			cannonBullet.body->SetBodyType(Body::BodyType::Kinematic);

			float offsetX = player->GetPosition().x - body->GetPosition().x;
			float offsetY = player->GetPosition().y - body->GetPosition().y;

			float angle = atan(offsetY / offsetX)*180/Pi;

			if (offsetX < 0) angle = angle + 180;

			cannonBullet.body->SetVelocity(2*cos(angle*Pi/180), 2*sin(angle*Pi/180));

			cannonBullet.body->SetPosition(body->GetPosition().x, body->GetPosition().y);

		}

	}

	if (stateTime >= 0)
	{
		stateTime += dt;

		if (stateTime > CIRCLEBULLETLIVETIME)
		{
			isBulletDestroyed = true;
			cannonBullet.body->SetBodyType(Body::BodyType::Static);
			stateTime = -1;
		}

	}



	cannonBullet.SetPosition(cannonBullet.body->GetPosition().x, cannonBullet.body->GetPosition().y);
}





