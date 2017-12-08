#include "Zoomer.h"



Zoomer::Zoomer()
{
}


Zoomer::~Zoomer()
{
}

void Zoomer::Create(World *world, Texture *skreeTexture)
{
	this->world = world;
	TexturePacker p = TexturePacker(skreeTexture, "Resources/enemies_packer.xml");

	zoomerAnimation.AddRegion(p.GetRegion("zoomer"));
	zoomerAnimation.SetFrameInterval(0.04);

	SetRegion(zoomerAnimation.GetKeyAnimation());
	SetSize(16, 14);
	SetPosition(16 * 73, 16 * 19);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Static;
	bodyDef.position.Set(16 * 73, 16 * 19);
	bodyDef.size.Set(16, 14);
	body = world->CreateBody(bodyDef);
	body->categoryBits = SKREE_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | BULLET_BIT;
	body->PutExtra(this);

}

void Zoomer::HandlePhysics()
{

}

void Zoomer::Render(SpriteBatch *batch)
{
	batch->Draw(*this);
}

void Zoomer::Update(float dt)
{

	//set sprite position
	this->SetPosition(body->GetPosition().x, body->GetPosition().y);


	SetRegion(zoomerAnimation.Next(dt));

}