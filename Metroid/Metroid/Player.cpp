#include "Player.h"



Player::Player()
{
}


Player::~Player()
{

}


void Player::Create(World *world)
{
	isJumping = false;
	isGrounded = true;
	isLookingup = false;
	isShooting = true;

	//get characterTexture
	characterTexture = Texture("Resources/samusaran_sheet.png");

	//get animations
	TexturePacker p = TexturePacker(&characterTexture, "Resources/samusaran_packer.xml");
	standingAnimation.AddRegion(p.GetRegion("standing"));
	movingAnimation.AddRegion(p.GetRegion("movewithoutshooting"));
	jumpingAnimation.AddRegion(p.GetRegion("jumpwithoutshooting"));
	standAndShootupAnimation.AddRegion(p.GetRegion("standandshootup"));
	moveAndShootAnimation.AddRegion(p.GetRegion("moveandshoot"));
	moveAndShootupAnimation.AddRegion(p.GetRegion("moveandshootup"));


	SetRegion(standingAnimation.GetKeyAnimation());
	SetSize(34, 66);
	SetPosition(16 * 8, 16 * 5);

	//setup mainbody
	mainBody.SetBodyType(Body::BodyType::Dynamic);
	mainBody.SetLinearDrag(10, 0.2);
	mainBody.SetMass(2);
	mainBody.SetID("Player");
	mainBody.SetSize(34, 66);
	mainBody.SetPosition(16 * 8, 16 * 5);
	//a small note: since "this" is actually a reference to this class, it will be no problem if you use the create method like this one.
	//but if you use the constructor method such as: Player(World &world) and later you write your code like this: player = Player(world)
	//this line of code will very likely cause you a problem of null pointer
	//in which case, putting this line of code into update method may be a solution
	mainBody.PutExtra(this);

	SetMainBody(&mainBody);

	//create foot
	//foot = new Body();
	foot.SetSize(25, 20);
	foot.IsSensor(true);
	foot.SetID("Foot");
	foot.PutExtra(this);

	world->AddBody(&mainBody);
	world->AddBody(&foot);

	


}


void Player::Update(float dt)
{
	if (!isGrounded)
	{
		SetRegion(jumpingAnimation.Next(dt));
	}
	else
	{
		if (!isLookingup)
		{
			//update state
			if (mainBody.GetVelocity().x == 0)
			{
				SetRegion(standingAnimation.Next(dt));
			}
			else
			{
				if (!isShooting)
				{
					SetRegion(movingAnimation.Next(dt));
				}
				else
				{
					SetRegion(moveAndShootAnimation.Next(dt));
				}
			}
		}
		else
		{
			if (mainBody.GetVelocity().x == 0)
			{
				SetRegion(standAndShootupAnimation.Next(dt));
			}
			else
			{
				SetRegion(moveAndShootupAnimation.Next(dt));
			}
		}
	}

	//flip if necessary
	if (mainBody.GetVelocity().x > 0)
	{
		this->Flip(false, false);
	}
	else
	{
		if (mainBody.GetVelocity().x < 0)
		{
			this->Flip(true, false);
		}
	}

	if (isJumping)
	{
		isGrounded = false;
		isJumping = false;
	}



	//update position
	SetPosition(mainBody.GetPosition().x, mainBody.GetPosition().y);
	foot.SetPosition(mainBody.GetPosition().x, mainBody.GetPosition().y - 30);
}


void Player::Release()
{
	characterTexture.Release();
	//delete mainBody;
	//delete foot;
}