#include "Skree.h"



Skree::Skree()
{
	
}


Skree::~Skree()
{
}

Skree::Skree(World *world, Texture *texture)
{
	TexturePacker p = TexturePacker(texture, "Resources/enemies_packer.xml");
	movingAnimation.AddRegion(p.GetRegion("skree"));
	movingAnimation.SetFrameInterval(0.04);

	SetRegion(movingAnimation.GetKeyAnimation());
	SetSize(16, 33);
	SetPosition(16 * 8, 16 * 10);
	
	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(16 * 8, 16 * 15);
	bodyDef.size.Set(16, 33);
	body = world->CreateBody(bodyDef);
	body->categoryBits = SKREE_BIT;

}


void Skree::HandleInput()
{

}

void Skree::Render(SpriteBatch *batch)
{

}

void Skree::Update(float dt)
{
	SetRegion(movingAnimation.Next(dt));
}
