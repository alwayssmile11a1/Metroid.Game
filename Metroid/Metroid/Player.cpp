#include "Player.h"



Player::Player()
{
}


Player::~Player()
{

}


void Player::Create(World &world)
{
	//SetSize(34, 66);

	//get characterTexture
	characterTexture = new Texture("Resources/samusaran_sheet.png");

	//get animations
	TexturePacker p = TexturePacker(characterTexture, "Resources/samusaran_packer.xml");
	standingAnimation.AddRegion(p.GetRegion("characterstand"));
	movingAnimation.AddRegion(p.GetRegion("charactermove"));

	//setup mainbody
	mainBody = new Body();
	mainBody->SetBodyType(Body::BodyType::Dynamic);
	mainBody->SetLinearDrag(10, 0.2);
	mainBody->SetMass(2);
	mainBody->SetID("Player");
	mainBody->SetSize(34, 66);
	

	//create foot
	foot = new Body();
	foot->SetSize(25, 20);
	foot->IsSensor(true);
	foot->SetID("Foot");


	world.AddBody(mainBody);
	world.AddBody(foot);

	SetRegion(standingAnimation.GetKeyAnimation());
	SetSize(34, 66);
	SetPosition(16 * 8, 16 * 5);
	FitBody();
}


void Player::Update(float dt)
{
	mainBody->PutExtra(this);
	foot->PutExtra(this);

	if (mainBody->GetVelocity().x == 0)
	{
		SetRegion(standingAnimation.Next(dt, -1));
	}
	else
	{
		if (mainBody->GetVelocity().x > 0)
		{
			SetRegion(movingAnimation.Next(dt, true));
		}
		else
		{
			SetRegion(movingAnimation.Next(dt, false));
		}
	}



	SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y);
	foot->SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y - 30);
}


void Player::Release()
{
	delete characterTexture;
	delete mainBody;
	delete foot;
}