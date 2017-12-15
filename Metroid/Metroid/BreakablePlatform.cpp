#include "BreakablePlatform.h"



BreakablePlatform::BreakablePlatform()
{
}


BreakablePlatform::~BreakablePlatform()
{
}

BreakablePlatform::BreakablePlatform(World *world,TMXMap*map, float x, float y, float width, float height)
{
	this->map = map;
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.size.Set(width, height);
	bodyDef.position.Set(x, y);
	body = world->CreateBody(bodyDef);
	body->categoryBits = BREAKABLEPLATFORM_BIT;
	body->maskBits = PLAYER_BIT | FOOT_BIT | BULLET_BIT | SKREE_BIT | ZOOMER_BIT | HEAD_BIT |EXPLOSION_BIT;
	body->PutExtra(this);
}

void BreakablePlatform::OnHitBomb()
{
	body->categoryBits = 0; // not collide more

	int column = (int)(body->GetPosition().x / map->GetTileWidth());
	int row = map->GetHeight() - (int)(body->GetPosition().y / map->GetTileHeight()) - 1;
	map->SetTileData(row, column, 0);

}
