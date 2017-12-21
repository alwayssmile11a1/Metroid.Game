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
	SetSize(30, 15);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(30, 15);
	bodyDef.isSensor = true;
	body = world->CreateBody(bodyDef);
	body->categoryBits = RIPPER_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | BULLET_BIT;
	body->PutExtra(this);

	
	//set up intial velocity/direction
	health = 2;
	hitBulletTime = -1;

	velocity.x = 0.7f;
	velocity.y = 0;
	body->SetVelocity(velocity.x, velocity.y);
}
void Ripper::Render(SpriteBatch *batch)
{
	if (isDead)
		return;

	batch->Draw(*this);
}

void Ripper::Update(float dt)
{
	if (isDead) return;

	if (health <= 0)
	{
		isDead = true;
		world->DestroyBody(body);
		return;
	}
	if (body != NULL)
		this->SetPosition(body->GetPosition().x, body->GetPosition().y);
	
	/*if (isHitGround)
	{
		velocity.x = -velocity.x;
		isHitGround = false;
	}
	body->SetVelocity(velocity.x, velocity.y);*/

}

void Ripper::OnHitGround()
{
	this->isHitGround = true;
}

void Ripper::OnHitBullet()
{
	if (hitBulletTime != -1) return;
	health--;
	hitBulletTime = 0;
	//stop this body a little bit 
	body->SetVelocity(0, 0);
}

void Ripper::OnHitPlayer()
{

}

bool Ripper::IsDead()
{
	return this->isDead;
}

void Ripper::ChangeDirection()
{		
	isHitGround = true;
	body->SetVelocity(-body->GetVelocity().x, 0);
}

int Ripper::GetHealth()
{
	return this->health;
}