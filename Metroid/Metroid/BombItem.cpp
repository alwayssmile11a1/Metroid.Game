#include "BombItem.h"



BombItem::BombItem()
{
}


BombItem::~BombItem()
{
}

void BombItem::Create(World *world, Texture *itemsTexture, int x, int y)
{
	this->world = world;

	TexturePacker p = TexturePacker(itemsTexture, "Resources/items_packer.xml");

	animation.AddRegion(p.GetRegion("bombitem"));
	animation.SetFrameInterval(0.2);

	SetRegion(*animation.GetKeyAnimation());
	SetSize(25, 32);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(25, 32);
	bodyDef.isSensor = true;
	body = world->CreateBody(bodyDef);
	body->categoryBits = BOMBITEM_BIT;
	body->maskBits = PLAYER_BIT;
	body->PutExtra(this);

	isHitPlayer = false;
}

void BombItem::Update(float dt)
{
	if (body == NULL) return;
	if (isHitPlayer)
	{
		world->DestroyBody(body);
		SetTexture(NULL);
		body = NULL;
		return;
	}
	SetRegion(*animation.Next(dt));
}

void BombItem::OnHitPlayer()
{
	isHitPlayer = true;
}