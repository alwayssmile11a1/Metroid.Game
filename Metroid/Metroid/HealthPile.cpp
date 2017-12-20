#include "HealthPile.h"



HealthPile::HealthPile()
{

}


HealthPile::~HealthPile()
{
}

void HealthPile::Create(World *world, Texture *texture, int x, int y)
{
	this->world = world;
	health = 30;

	TexturePacker p = TexturePacker(texture, "Resources/bosses_packer.xml");

	regions = p.GetRegion("healthpile");

	SetRegion(regions.front());
	SetSize(24, 64);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(24, 64);
	body = world->CreateBody(bodyDef);
	body->categoryBits = PLATFORM_BIT;
	body->maskBits = PLAYER_BIT;
	body->PutExtra(this);

	//setup body2
	BodyDef body2Def;
	body2Def.bodyType = Body::BodyType::Kinematic;
	body2Def.position.Set(x, y);
	body2Def.size.Set(30, 64);
	body2Def.isSensor = true;
	body2 = world->CreateBody(body2Def);
	body2->categoryBits = HEALTHPILE_BIT;
	body2->maskBits = BULLET_BIT | EXPLOSION_BIT;
	body2->PutExtra(this);
}


void HealthPile::Render(SpriteBatch *batch)
{
	if (body == NULL) return;
	batch->Draw(*this);
}

void HealthPile::Update(float dt)
{
	if (body == NULL) return;

	if (health <= 20 && health >10)
	{
		SetRegion(regions.at(1));
		body->SetSize(20, 64);
	}
	else
	{
		if (health <= 10 && health >0)
		{
			SetRegion(regions.back());
			body->SetSize(10, 64);
		}
		else
		{
			if (health <= 0)
			{
				SetTexture(NULL);
				world->DestroyBody(body);
				world->DestroyBody(body2);
				body = NULL;
			}
		}
	}


}


void HealthPile::OnHitBullet()
{
	health--;
}

void HealthPile::OnHitBomb()
{
	health -= 3;
}

bool HealthPile::IsDead()
{
	return health <= 0;
}
