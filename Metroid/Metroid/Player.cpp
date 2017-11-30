#include "Player.h"



Player::Player()
{
	
}


Player::~Player()
{

}


void Player::Create(World *world)
{
	this->world = world;

	isGrounded = true;
	isLookingup = false;
	isShooting = true;

	lastShot = 0;

	jumpTime = 0;

	//get characterTexture
	characterTexture = Texture("Resources/samusaran_sheet.png");
	bulletTexture = Texture("Resources/samusaran_sheet.png");

	//get animations
	TexturePacker p = TexturePacker(&characterTexture, "Resources/samusaran_packer.xml");
	standingAnimation.AddRegion(p.GetRegion("standing"));
	movingAnimation.AddRegion(p.GetRegion("movewithoutshooting"));
	jumpingAnimation.AddRegion(p.GetRegion("jumpwithoutshooting"));
	standAndShootupAnimation.AddRegion(p.GetRegion("standandshootup"));
	moveAndShootAnimation.AddRegion(p.GetRegion("moveandshoot"));
	moveAndShootupAnimation.AddRegion(p.GetRegion("moveandshootup"));
	jumpAndShootAnimation.AddRegion(p.GetRegion("jumpandshoot"));
	jumpAndShootupAnimation.AddRegion(p.GetRegion("jumpandshootup"));


	SetRegion(standingAnimation.GetKeyAnimation());
	SetSize(34, 66);
	SetPosition(16 * 8, 16 * 7);

	//setup mainbody
	mainBody.SetBodyType(Body::BodyType::Dynamic);
	mainBody.SetLinearDrag(10, 0.2);
	mainBody.SetMass(2);
	mainBody.SetID("Player");
	mainBody.SetSize(34, 66);
	mainBody.SetPosition(16 * 8, 16 * 7);
	mainBody.categoryBits = PLAYER_BIT;
	//a small note: since "this" is actually a reference to this class, it will be no problem if you use the create method like this one.
	//but if you use the constructor method such as: Player(World &world) and later you write your code like this: player = Player(world)
	//this line of code will very likely cause you a problem of null pointer
	//in which case, putting this line of code into update method may be a solution
	mainBody.PutExtra(this);


	//create foot
	//foot = new Body();
	foot.SetBodyType(Body::BodyType::Kinematic);
	foot.SetSize(30, 20);
	foot.IsSensor(true);
	foot.SetID("Foot");
	foot.categoryBits = FOOT_BIT;
	foot.PutExtra(this);

	world->AddBody(&mainBody);
	world->AddBody(&foot);

	


}

void Player::HandleInput()
{
	if (input.GetKey(DIK_RIGHT))
	{
		mainBody.SetVelocity(5, mainBody.GetVelocity().y);
	}

	if (input.GetKey(DIK_LEFT))
	{
		mainBody.SetVelocity(-5, mainBody.GetVelocity().y);

	}
	
	if (input.GetKey(DIK_Z))
	{
		if (jumpTime < MAXJUMPTIME)
		{
			mainBody.SetVelocity(mainBody.GetVelocity().x, mainBody.GetVelocity().y + 0.3f);
			jumpTime += 0.02f;
		}
		else
		{
			jumpTime = 100;
		}
	}
	else
	{
		jumpTime = 100; //don't jump more
	}

	if (input.GetKeyDown(DIK_Z) && isGrounded)
	{
		mainBody.SetVelocity(mainBody.GetVelocity().x, 5);
		isGrounded = false;
		jumpTime = 0;
	}


	
	

	if (input.GetKey(DIK_UPARROW))
	{
		isLookingup = true;
	}
	else
	{
		isLookingup = false;
	}

	if (input.GetKeyDown(DIK_X))
	{
		isShooting = true;
	}

	if (input.GetKey(DIK_X))
	{
		isShooting = true;
	}
	else
	{
		isShooting = false;
	}

	if (isShooting)
	{
		Fire();
	}

}

void Player::Fire()
{
	float currentTime = GetTickCount() / 1000.0f;
	if (currentTime > FIRERATE + lastShot)
	{
		//instantiate bullet
		Bullet* bullet = new Bullet(world, &bulletTexture);
		Vector2 position;
		Vector2 velocity;
		if (isLookingup)
		{
			position.x = GetPosition().x;
			position.y = GetPosition().y + GetSize().y / 2 + bullet->GetSize().y / 2;
			velocity.Set(0, BULLETSPEED);
		}
		else
		{
			if (!IsFlipX())
			{
				position.x = GetPosition().x + GetSize().x / 2 + bullet->GetSize().x / 2;
				position.y = GetPosition().y + 10;
				velocity.Set(BULLETSPEED, 0);
			}
			else
			{
				position.x = GetPosition().x - GetSize().x / 2 - bullet->GetSize().x / 2;
				position.y = GetPosition().y + 10;
				velocity.Set(-BULLETSPEED, 0);
			}
		}

		bullet->GetMainBody()->SetPosition(position.x, position.y);
		bullet->GetMainBody()->SetVelocity(velocity.x, velocity.y);
		bullets.push_back(bullet);


		lastShot = currentTime;

	}

	
}

void Player::OnGrounded()
{
	isGrounded = true;
	jumpTime = 100;
}


void Player::Render(SpriteBatch *batch)
{
	//draw bullets
	for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
	{
		(*it)->Render(*batch);
	}

	//draw player
	batch->Draw(*this);
}


void Player::Update(float dt)
{
	if (!isGrounded)
	{
		if (!isLookingup)
		{
			if (!isShooting)
			{
				SetRegion(jumpingAnimation.Next(dt));
			}
			else
			{
				SetRegion(jumpAndShootAnimation.Next(dt));
			}
			
		}
		else
		{
			SetRegion(jumpAndShootupAnimation.Next(dt));
		}

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


	//update position
	SetPosition(mainBody.GetPosition().x, mainBody.GetPosition().y);
	foot.SetPosition(mainBody.GetPosition().x, mainBody.GetPosition().y - 35);

	//update bullet
	for (int i = 0; i < bullets.size(); i++)
	{
		Bullet* currentBullet = bullets[i];
		currentBullet->Update(dt);
		if (currentBullet->IsDestroyed())
		{
			delete currentBullet;
			bullets.erase(bullets.begin() + i);
		}
	}
	

	
}


void Player::Release()
{
	characterTexture.Release();
	bulletTexture.Release();
	//draw bullets
	for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
	{
		delete (*it);
	}

	//delete mainBody;
	//delete foot;
}