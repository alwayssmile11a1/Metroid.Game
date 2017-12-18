#include "MotherBrain.h"



MotherBrain::MotherBrain()
{

}


MotherBrain::~MotherBrain()
{
}

void MotherBrain::Create(World *world, Texture *skreeTexture, int x, int y)
{
	health = 20;

	TexturePacker p = TexturePacker(skreeTexture, "Resources/bosses_packer.xml");

	animation.AddRegion(p.GetRegion("motherbrain"));
	animation.SetFrameInterval(0.2);

	weakAnimation.AddRegion(p.GetRegion("weakmotherbrain"));
	weakAnimation.SetFrameInterval(0.2);


	SetRegion(*animation.GetKeyAnimation());
	SetSize(80, 65);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(80, 65);
	bodyDef.isSensor = true;
	body = world->CreateBody(bodyDef);
	body->categoryBits = MOTHERBRAIN_BIT;
	body->maskBits = PLAYER_BIT| BULLET_BIT | EXPLOSION_BIT;
	body->PutExtra(this);

}


void MotherBrain::Render(SpriteBatch *batch)
{
	batch->Draw(*this);
}

void MotherBrain::Update(float dt)
{
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

int MotherBrain::GetHealth()
{
	return health;
}