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
	characterTexture = Texture("Resources/samusaran_sheet.png");

	//get animations
	TexturePacker p = TexturePacker(&characterTexture, "Resources/samusaran_packer.xml");
	standingAnimation.AddRegion(p.GetRegion("characterstand"));
	movingAnimation.AddRegion(p.GetRegion("charactermove"));

	//setup mainbody
	mainBody.SetBodyType(Body::BodyType::Dynamic);
	mainBody.SetLinearDrag(10, 0.2);
	mainBody.SetMass(2);
	mainBody.SetID("Player");
	mainBody.SetSize(34, 66);
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

	world.AddBody(&mainBody);
	world.AddBody(&foot);

	SetRegion(standingAnimation.GetKeyAnimation());
	SetSize(34, 66);
	SetPosition(16 * 8, 16 * 5);
	FitBody();
}


void Player::Update(float dt)
{

	//update state
	if (mainBody.GetVelocity().x == 0)
	{
		SetRegion(standingAnimation.Next(dt, -1));
	}
	else
	{
		if (mainBody.GetVelocity().x > 0)
		{
			SetRegion(movingAnimation.Next(dt, true));
		}
		else
		{
			SetRegion(movingAnimation.Next(dt, false));
		}
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