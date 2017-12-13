#include "HealthItem.h"



HealthItem::HealthItem()
{
}


HealthItem::~HealthItem()
{
}

void HealthItem::Create(World *world, Texture *itemsTexture, int x, int y)
{
	this->world = world;

	TexturePacker p = TexturePacker(itemsTexture, "Resources/items_packer.xml");

	animation.AddRegion(p.GetRegion("healthItem"));

	SetRegion(animation.GetKeyAnimation());
	SetSize(10, 10);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(10, 10);
	bodyDef.isSensor = true;
	body = world->CreateBody(bodyDef);
	body->categoryBits = HEALTHITEM_BIT;
	body->maskBits = PLAYER_BIT;
	body->PutExtra(this);

	isHitPlayer = false;
}

void HealthItem::Render(SpriteBatch *batch)
{
	if (isHitPlayer) return;
	batch->Draw(*this);
}

void HealthItem::Update(float dt)
{
	if (isHitPlayer)
	{
		world->DestroyBody(body);
		SetTexture(NULL);
		return;
	}
	SetRegion(animation.Next(dt));
}

void HealthItem::OnHitPlayer()
{
	isHitPlayer = true;
}