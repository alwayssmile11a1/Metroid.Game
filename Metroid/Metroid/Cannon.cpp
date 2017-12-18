#include "Cannon.h"



Cannon::Cannon()
{

}


Cannon::~Cannon()
{
}

void Cannon::Create(World *world, Texture *skreeTexture, int x, int y)
{
	this->world = world;
	lastShot = 0;

	TexturePacker p = TexturePacker(skreeTexture, "Resources/bosses_packer.xml");

	cannonAnimation.AddRegion(p.GetRegion("cannon"));
	
	bulletAnimation.AddRegion(p.GetRegion("cannonbullet"));

	SetRegion(*cannonAnimation.GetKeyAnimation());
	SetSize(17, 17);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(17, 17);
	body = world->CreateBody(bodyDef);
	body->categoryBits = CANNON_BIT;
	body->maskBits = PLAYER_BIT;
	body->PutExtra(this);


}
void Cannon::HandlePhysics()
{

}

void Cannon::Render(SpriteBatch *batch)
{
	batch->Draw(*this);
}

void Cannon::Update(float dt)
{
	float currentTime = GetTickCount() / 1000.0f;
	if (currentTime > CANNOTFIRERATE + lastShot) //don't shoot more if we have just shooted 
	{
		
		SetRegion(*cannonAnimation.Next(dt));
		


		lastShot = currentTime;

	}

}


void Cannon::OnHitBullet()
{

}

void Cannon::OnHitBomb()
{
	
}

