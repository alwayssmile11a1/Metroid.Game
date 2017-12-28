#include "AirHole.h"

AirHole::AirHole()
{

}

AirHole::~AirHole()
{

}

void AirHole::Create(World *world, Texture* airHoleTexture, int x, int y)
{
	this->world = world;

	TexturePacker p = TexturePacker(airHoleTexture, "Resources/airhole.xml");

	airHoleAnimation.AddRegion(p.GetRegion("door").at(0));


	SetRegion(*airHoleAnimation.GetKeyAnimation());
	SetSize(32, 10);
	SetPosition(x , y);

	//setup bodyRight
	BodyDef bodyDefAirHole;
	bodyDefAirHole.bodyType = Body::BodyType::Static;
	bodyDefAirHole.position.Set(x , y);
	bodyDefAirHole.size.Set(32, 10);

	//bodyDefRight.isSensor = true;
	body = world->CreateBody(bodyDefAirHole);
	//body->categoryBits = DOOR_BIT;
	body->maskBits = PLAYER_BIT;
	body->PutExtra(this);
}

void AirHole::Render(SpriteBatch *batch)
{
	batch->Draw(*this);
}