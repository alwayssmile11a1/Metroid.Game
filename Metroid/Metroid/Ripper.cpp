#include "Ripper.h"
Ripper::Ripper()
{
}


Ripper::~Ripper()
{
}

void Ripper::Create(World *world, Texture *ripperTexture, int x, int y)
{
	this->world = world;
	TexturePacker p = TexturePacker(ripperTexture, "Resources/enemies_packer.xml");

	ripperAnimation.AddRegion(p.GetRegion("ripper"));
	//zoomerAnimation.SetFrameInterval(0.04);

	SetRegion(*ripperAnimation.GetKeyAnimation());
	SetSize(25, 25);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(25, 25);
	body = world->CreateBody(bodyDef);
	body->categoryBits = RIPPER_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | BULLET_BIT | BREAKABLEPLATFORM_BIT;
	body->PutExtra(this);

	
	//set up intial velocity/direction
	health = 2;
	hitBulletTime = -1;
}
void Ripper::Render(SpriteBatch *batch)
{
	if (isDead)
		return;

	batch->Draw(*this);
}