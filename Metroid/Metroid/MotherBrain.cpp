#include "MotherBrain.h"



MotherBrain::MotherBrain()
{

}


MotherBrain::~MotherBrain()
{
}

void MotherBrain::Create(World *world, Texture *texture, int x, int y)
{
	this->world = world;
	health = 20;

	TexturePacker p = TexturePacker(texture, "Resources/bosses_packer.xml");

	animation.AddRegion(p.GetRegion("motherbrain"));
	animation.SetFrameInterval(0.2);

	weakAnimation.AddRegion(p.GetRegion("weakmotherbrain"));
	weakAnimation.SetFrameInterval(0.2);


	SetRegion(*animation.GetKeyAnimation());
	SetSize(160, 130);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(160, 130);
	bodyDef.isSensor = true;
	body = world->CreateBody(bodyDef);
	body->categoryBits = MOTHERBRAIN_BIT;
	body->maskBits = PLAYER_BIT| BULLET_BIT | EXPLOSION_BIT;
	body->PutExtra(this);
}

void MotherBrain::Create(World *world, Texture *texture, Body* body)
{
	this->world = world;
	health = 20;

	TexturePacker p = TexturePacker(texture, "Resources/bosses_packer.xml");

	animation.AddRegion(p.GetRegion("motherbrain"));
	animation.SetFrameInterval(0.2);

	weakAnimation.AddRegion(p.GetRegion("weakmotherbrain"));
	weakAnimation.SetFrameInterval(0.2);


	SetRegion(*animation.GetKeyAnimation());
	SetSize(160, 130);
	SetPosition(body->GetPosition().x, body->GetPosition().y);

	//setup body
	this->body = body;
	body->SetBodyType(Body::BodyType::Kinematic);
	body->SetSize(160, 130);
	body->IsSensor(true);
	body->categoryBits = MOTHERBRAIN_BIT;
	body->maskBits = PLAYER_BIT | BULLET_BIT | EXPLOSION_BIT;
	body->PutExtra(this);
}

void MotherBrain::Render(SpriteBatch *batch)
{
	if (body == NULL) return;
	batch->Draw(*this);
}

void MotherBrain::Update(float dt)
{
	if (body == NULL) return;
	if (health <= 0)
	{
		world->DestroyBody(body);
		body = NULL;

	}


	if (health > 10)
	{
		SetRegion(*animation.Next(dt));
	}
	else
	{
		SetRegion(*weakAnimation.Next(dt));
	}


}


void MotherBrain::OnHitBullet()
{
	health--;
}

void MotherBrain::OnHitBomb()
{
	health -= 3;
}

bool MotherBrain::IsDead()
{
	return health<=0;
}
