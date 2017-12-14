#include "Player.h"



Player::Player()
{
	
}


Player::~Player()
{

}


void Player::Create(World *world, float x, float y)
{
	this->world = world;

	isGrounded = false;
	isLookingup = false;
	isShooting = false;
	canRoll = false;

	lastShot = 0;

	jumpTime = 0;

	health = 30;

	beingHitTime = -1; //not being hit

	//get characterTexture
	texture = Texture("Resources/metroidfullsheet.png");

	//get animations
	TexturePacker p = TexturePacker(&texture, "Resources/samusaran_packer.xml");
	appearingAnimation.AddRegion(p.GetRegion("appearing"));
	appearingAnimation.SetFrameInterval(0.05);
	standingAnimation.AddRegion(p.GetRegion("standing"));
	movingAnimation.AddRegion(p.GetRegion("movewithoutshooting"));
	jumpingAnimation.AddRegion(p.GetRegion("jumpwithoutshooting"));
	standAndShootupAnimation.AddRegion(p.GetRegion("standandshootup"));
	moveAndShootAnimation.AddRegion(p.GetRegion("moveandshoot"));
	moveAndShootupAnimation.AddRegion(p.GetRegion("moveandshootup"));
	jumpAndShootAnimation.AddRegion(p.GetRegion("jumpandshoot"));
	jumpAndShootupAnimation.AddRegion(p.GetRegion("jumpandshootup"));
	rollingAnimation.AddRegion(p.GetRegion("rolling"));
	jumpAndRollAnimation.AddRegion(p.GetRegion("jumpandroll"));
	beingHitAnimation.AddRegion(p.GetRegion("beinghit"));

	//SETUP STATE MANAGER - THIS WAY IS EVEN MUCH MORE DIFFICULT THAN THE NORMAL WAY (LOL) 
	//						BUT THIS MAYBE MORE VISUALIZABLE
	//add condition 
	characterStateManager.AddCondition("grounded");
	characterStateManager.AddCondition("lookingup");
	characterStateManager.AddCondition("shooting");
	characterStateManager.AddCondition("moving");
	characterStateManager.AddCondition("rolling");

	characterStateManager.SetCurrentAnimation(&standingAnimation);

	//add transition animation
	characterStateManager.Add(&standingAnimation, &movingAnimation, { Condition("moving", Condition::ConditionType::Greater, 0) });
	characterStateManager.Add(&movingAnimation, &standingAnimation, { Condition("moving", Condition::ConditionType::Equal, 0) });

	characterStateManager.Add(&standingAnimation, &rollingAnimation, { Condition("rolling", Condition::ConditionType::Equal, true) });
	characterStateManager.Add(&rollingAnimation, &standingAnimation, { Condition("rolling", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&standingAnimation, &jumpingAnimation, { Condition("grounded", Condition::ConditionType::Equal, false) });
	characterStateManager.Add(&jumpingAnimation, &standingAnimation, { Condition("grounded", Condition::ConditionType::Equal, true) });

	characterStateManager.Add(&standingAnimation, &standAndShootupAnimation, { Condition("lookingup", Condition::ConditionType::Equal, true) });
	characterStateManager.Add(&standAndShootupAnimation, &standingAnimation, { Condition("lookingup", Condition::ConditionType::Equal, false) });
	
	characterStateManager.Add(&movingAnimation, &moveAndShootAnimation, { Condition("shooting", Condition::ConditionType::Equal, true) });
	characterStateManager.Add(&moveAndShootAnimation, &movingAnimation, { Condition("shooting", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&movingAnimation, &moveAndShootupAnimation, { Condition("lookingup", Condition::ConditionType::Equal, true) });
	characterStateManager.Add(&moveAndShootupAnimation, &movingAnimation, { Condition("lookingup", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&jumpingAnimation, &jumpAndShootAnimation, { Condition("shooting", Condition::ConditionType::Equal, true) });
	characterStateManager.Add(&jumpAndShootAnimation, &jumpingAnimation, { Condition("shooting", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&jumpingAnimation, &jumpAndShootupAnimation, { Condition("lookingup", Condition::ConditionType::Equal, true) });
	characterStateManager.Add(&jumpAndShootupAnimation, &jumpingAnimation, { Condition("lookingup", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&jumpAndShootAnimation, &jumpAndShootupAnimation, { Condition("lookingup", Condition::ConditionType::Equal, true) });
	characterStateManager.Add(&jumpAndShootupAnimation, &jumpAndShootAnimation, { Condition("lookingup", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&movingAnimation, &jumpingAnimation, { Condition("grounded", Condition::ConditionType::Equal, false) });
	characterStateManager.Add(&jumpingAnimation, &movingAnimation, { Condition("grounded", Condition::ConditionType::Equal, true) });
	
	characterStateManager.Add(&moveAndShootAnimation, &standingAnimation, { Condition("moving", Condition::ConditionType::Equal, 0) });

	characterStateManager.Add(&moveAndShootupAnimation, &standingAnimation, { Condition("moving", Condition::ConditionType::Equal, 0) });

	characterStateManager.Add(&standAndShootupAnimation, &movingAnimation, { Condition("moving", Condition::ConditionType::Greater, 0) });

	characterStateManager.Add(&moveAndShootAnimation, &moveAndShootupAnimation, { Condition("lookingup", Condition::ConditionType::Equal, true) });

	characterStateManager.Add(&jumpAndShootAnimation, &standingAnimation, { Condition("grounded", Condition::ConditionType::Equal, true) });

	characterStateManager.Add(&jumpAndShootupAnimation, &standingAnimation, { Condition("grounded", Condition::ConditionType::Equal, true) });

	characterStateManager.Add(&standAndShootupAnimation, &jumpingAnimation, { Condition("grounded", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&standAndShootupAnimation, &jumpingAnimation, { Condition("grounded", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&standAndShootupAnimation, &jumpingAnimation, { Condition("grounded", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&moveAndShootAnimation, &jumpingAnimation, { Condition("grounded", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&moveAndShootupAnimation, &jumpingAnimation, { Condition("grounded", Condition::ConditionType::Equal, false) });

	//ANOTHER JUST-MAYBE-EASIER WAY AROUND STATE MANAGER: 
	//we have 3 main animations: standing, moving and jumping
	//if isGrounded == true, set characterStateManager.CurrentAnimation to standing animation
	//if isGrounded == false, set characterStateManager.CurrentAnimation to jumping animation
	//........


	//set size and position
	SetRegion(*appearingAnimation.GetKeyAnimation());
	SetSize(34, 60);
	SetPosition(x, y);

	
	//setup mainbody
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Dynamic;
	bodyDef.linearDrag.Set(10, 0.2);
	bodyDef.mass = 2;
	bodyDef.size.Set(30, 60);
	bodyDef.position.Set(x, y);
	mainBody = world->CreateBody(bodyDef);
	mainBody->categoryBits = PLAYER_BIT;
	mainBody->maskBits = SKREE_BIT | ZOOMER_BIT | PLATFORM_BIT | ROLLITEM_BIT | HEALTHITEM_BIT;
	//a small note: since "this" is actually a reference to this class, it will be no problem if you use the create method like this one.
	//but if you use the constructor method such as: Player(World &world) and later you write your code like this: player = Player(world)
	//this line of code will very likely cause you a problem of null pointer
	//in which case, putting this line of code into update method may be a solution
	mainBody->PutExtra(this);


	//create foot
	BodyDef footDef;
	footDef.bodyType = Body::BodyType::Kinematic;
	footDef.size.Set(30, 5);
	footDef.isSensor= true;
	foot = world->CreateBody(footDef);
	foot->categoryBits = FOOT_BIT;
	foot->maskBits = PLATFORM_BIT;
	foot->PutExtra(this);

	//create head
	BodyDef headDef;
	headDef.bodyType = Body::BodyType::Kinematic;
	headDef.size.Set(30, 5);
	headDef.isSensor = true;
	head = world->CreateBody(headDef);
	head->categoryBits = HEAD_BIT;
	head->maskBits = PLATFORM_BIT;
	head->PutExtra(this);

}

void OnFinishAppearing()
{

}

void Player::HandleInput()
{
	if (input.GetKey(DIK_RIGHT))
	{
		mainBody->SetVelocity(5, mainBody->GetVelocity().y);
	}

	if (input.GetKey(DIK_LEFT))
	{
		mainBody->SetVelocity(-5, mainBody->GetVelocity().y);

	}

	if (input.GetKeyDown(DIK_DOWN) && canRoll && isGrounded && mainBody->GetVelocity().x==0)
	{
		mainBody->SetSize(mainBody->GetSize().x, 25);
		isRolling = true;
	}

	if (input.GetKey(DIK_Z))
	{
		if (jumpTime < MAXJUMPTIME)
		{
			mainBody->SetVelocity(mainBody->GetVelocity().x, mainBody->GetVelocity().y + 0.3f);
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
		mainBody->SetVelocity(mainBody->GetVelocity().x, 6);
		isGrounded = false;
		jumpTime = 0;
	}

	if (!isHeadHit) // if not being hit on head, player can transform back to original size 
	{
		if (input.GetKeyDown(DIK_UP) || input.GetKeyDown(DIK_Z))
		{
			mainBody->SetSize(mainBody->GetSize().x, 60);
			if (isRolling)
			{
				isGrounded = true;
			}
			isRolling = false;
		}
	}
	else
	{
		isHeadHit = false;
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

	if (input.GetKey(DIK_X) && !isRolling)
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
		Bullet* bullet = new Bullet(world, &texture);
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


		//PLAY SOUND HERE


	}

	
}

void Player::OnAppearing(float dt)
{
	SetRegion(*appearingAnimation.Next(dt));
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
	//if (!isGrounded)
	//{
	//	if (!isLookingup)
	//	{
	//		if (!isShooting)
	//		{
	//			SetRegion(jumpingAnimation.Next(dt));
	//		}
	//		else
	//		{
	//			SetRegion(jumpAndShootAnimation.Next(dt));
	//		}
	//		
	//	}
	//	else
	//	{
	//		SetRegion(jumpAndShootupAnimation.Next(dt));
	//	}

	//}
	//else
	//{
	//	if (!isLookingup)
	//	{
	//		//update state
	//		if (mainBody->GetVelocity().x == 0)
	//		{
	//			SetRegion(standingAnimation.Next(dt));
	//		}
	//		else
	//		{
	//			if (!isShooting)
	//			{
	//				SetRegion(movingAnimation.Next(dt));
	//			}
	//			else
	//			{
	//				SetRegion(moveAndShootAnimation.Next(dt));
	//			}
	//		}
	//	}
	//	else
	//	{
	//		if (mainBody->GetVelocity().x == 0)
	//		{
	//			SetRegion(standAndShootupAnimation.Next(dt));
	//		}
	//		else
	//		{
	//			SetRegion(moveAndShootupAnimation.Next(dt));
	//		}
	//	}
	//}

	if (beingHitTime == -1) //not being hit
	{
		characterStateManager.Set("moving", abs(mainBody->GetVelocity().x));
		characterStateManager.Set("grounded", isGrounded);
		characterStateManager.Set("lookingup", isLookingup);
		characterStateManager.Set("shooting", isShooting);
		characterStateManager.Set("rolling", isRolling);

		SetRegion(*characterStateManager.GetTargetAnimation()->Next(dt));
	}
	else //being hit
	{
		if (beingHitTime == 0) //push player a little to left or right only one time
		{
			if (beingRightHit)
			{
				mainBody->SetVelocity(-15, 5);
			}
			else
			{
				mainBody->SetVelocity(15, 5);
			}
		}

		if (beingHitTime < MAXUNTOUCHABLETIME)
		{
			SetRegion(*beingHitAnimation.Next(dt));
			beingHitTime += dt;
		}
		else
		{
			beingHitTime = -1;
		}
		
	}

	//flip if necessary
	if (mainBody->GetVelocity().x > 0)
	{
		this->Flip(false, false);
	}
	else
	{
		if (mainBody->GetVelocity().x < 0)
		{
			this->Flip(true, false);
		}
	}


	//update position
	SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y);
	foot->SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y - 30);
	head->SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y + 30);

	//update bullet
	for (int i = 0; i < bullets.size(); i++)
	{
		Bullet* currentBullet = bullets[i];
		currentBullet->Update(dt);
		if (currentBullet->IsDestroyed())
		{
			delete currentBullet;
			currentBullet = NULL;
			bullets.erase(bullets.begin() + i);
		}
	}
	

	
}

void Player::OnHeadHit()
{
	isHeadHit = true;
}

void Player::OnHitRollItem()
{
	canRoll = true;
}

void Player::OnHitHealthItem()
{
	health += 6;
}

void Player::OnHitEnemy(bool rightHit)
{
	if (beingHitTime != -1) return; //if beinghittime !=-1, it means player has just been hit and we don't want it to be hit in this time
	health -= 8;
	SetRegion(*beingHitAnimation.GetKeyAnimation());
	beingHitTime = 0;
	beingRightHit = rightHit;
}

int  Player::GetHealth()
{
	return health;
}



void Player::Release()
{
	//characterTexture.Release();
	//bulletTexture.Release();
	//draw bullets
	for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
	{
		delete (*it);
	}

	//delete mainBody;
	//delete foot;
}