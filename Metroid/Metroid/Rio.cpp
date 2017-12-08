#include "Rio.h"



Rio::Rio()
{
}


Rio::~Rio()
{
}

void Rio::Create(World *world, Texture *skreeTexture)
{
	this->world = world;
	TexturePacker p = TexturePacker(skreeTexture, "Resources/enemies_packer.xml");

	rioAnimation.AddRegion(p.GetRegion("rio"));
	rioAnimation.SetFrameInterval(0.04);

	SetRegion(rioAnimation.GetKeyAnimation());
	SetSize(24, 19);
	SetPosition(16 * 72, 16 * 19);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.position.Set(16 * 65, 16 * 19);
	bodyDef.size.Set(24, 19);
	body = world->CreateBody(bodyDef);
	body->categoryBits = SKREE_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | BULLET_BIT;
	body->PutExtra(this);

}

void Rio::HandlePhysics()
{

}

void Rio::Render(SpriteBatch *batch)
{
	batch->Draw(*this);
}

void Rio::Update(float dt)
{

	//set sprite position
	this->SetPosition(body->GetPosition().x, body->GetPosition().y);


	SetRegion(rioAnimation.Next(dt));

}