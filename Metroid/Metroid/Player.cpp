#include "Player.h"



Player::Player()
{
}


Player::~Player()
{

}

Player::Player(World &world)
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


void Player::HandleInput(float dt)
{
	if (mainBody->GetVelocity().x == 0)
	{
		SetRegion(standingAnimation.Next(dt,-1));
	}

	if (input.GetKey(DIK_RIGHT))
	{
		mainBody->SetVelocity(5, mainBody->GetVelocity().y);
		SetRegion(movingAnimation.Next(dt, true));
	}

	if (input.GetKey(DIK_LEFT))
	{
		mainBody->SetVelocity(-5, mainBody->GetVelocity().y);
		SetRegion(movingAnimation.Next(dt, false));
	}

	if (input.GetKeyDown(DIK_SPACE) && isGrounded && !isJumping)
	{
		mainBody->SetVelocity(mainBody->GetVelocity().x, 8);
		isGrounded = false;
		isJumping = true;
	}
}

void Player::Release()
{
	delete characterTexture;
	delete mainBody;
	delete foot;
}