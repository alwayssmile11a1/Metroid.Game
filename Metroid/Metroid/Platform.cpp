#include "Platform.h"



Platform::Platform()
{
}


Platform::~Platform()
{
}

Platform::Platform(World *world, float x, float y, float width, float height)
{
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.size.Set(width, height);
	bodyDef.position.Set(x, y);
	Body* body = world->CreateBody(bodyDef);
	body->categoryBits = PLATFORM_BIT;
	body->maskBits = PLAYER_BIT|FOOT_BIT|BULLET_BIT|SKREE_BIT|ZOOMER_BIT|HEAD_BIT|RIO_BIT|CANNON_BIT|KRAID_BIT|RIPPER_BIT;
	
}

Platform::Platform(Body* body)
{
	body->SetBodyType(Body::BodyType::Static);
	body->categoryBits = PLATFORM_BIT;
	body->maskBits = PLAYER_BIT | FOOT_BIT | BULLET_BIT | SKREE_BIT | ZOOMER_BIT | HEAD_BIT | RIO_BIT | CANNON_BIT | KRAID_BIT | RIPPER_BIT;
}