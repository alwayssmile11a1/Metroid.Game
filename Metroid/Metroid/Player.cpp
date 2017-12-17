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

	isGrounded = true;
	isLookingup = false;
	isShooting = false;
	canRoll = true;
	canBomb = true;
	isBombing = false;

	lastShot = 0;

	jumpTime = 0;

	health = 30;

	beingHitTime = -1; //not being hit

	deadTime = -1;

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

	characterStateManager.Add(&standingAnimation, &rollingAnimation, { Condition("rolling", Condition::ConditionType::Equal, true) });

	characterStateManager.Add(&standingAnimation, &jumpingAnimation, { Condition("grounded", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&standingAnimation, &standAndShootupAnimation, { Condition("lookingup", Condition::ConditionType::Equal, true) });

	characterStateManager.Add(&movingAnimation, &rollingAnimation, { Condition("rolling", Condition::ConditionType::Equal, true) });

	characterStateManager.Add(&movingAnimation, &moveAndShootAnimation, { Condition("shooting", Condition::ConditionType::Equal, true),
																			Condition("lookingup", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&movingAnimation, &moveAndShootupAnimation, { Condition("lookingup", Condition::ConditionType::Equal, true) });

	characterStateManager.Add(&jumpingAnimation, &jumpAndRollAnimation, { Condition("moving", Condition::ConditionType::Greater, 0),
																			Condition("shooting", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&jumpingAnimation, &jumpAndShootAnimation, { Condition("shooting", Condition::ConditionType::Equal, true),
																			Condition("lookingup", Condition::ConditionType::Equal, false) });

	characterStateManager.Add(&jumpingAnimation, &jumpAndShootupAnimation, { Condition("lookingup", Condition::ConditionType::Equal, true) });



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
	mainBody->maskBits = SKREE_BIT | ZOOMER_BIT | PLATFORM_BIT | MARUMARIITEM_BIT | HEALTHITEM_BIT | BOMBITEM_BIT | EXPLOSION_BIT |BREAKABLEPLATFORM_BIT|RIO_BIT;
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
	foot->maskBits = PLATFORM_BIT| BREAKABLEPLATFORM_BIT;
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


	//bomb
	bomb = NULL;


	//Setup Dead effect
	Sprite deadEffectSprite;
	deadEffectSprite.SetRegion(p.GetRegion("deadeffect").front());
	deadEffectSprite.SetSize(8, 8);
	for (int i = 0; i < 8; i++)
	{
		deadEffectSprite.SetRotation(i * 30);
		deadEffect.push_back(deadEffectSprite);
	}



	//Iteam Acquisition Sound
	itemAcquisition = sound.LoadSound("Resources/SoundEffect/ItemAcquisition.wav");
}


void Player::HandleInput()
{
	if (deadTime > MAXDEADTIME)
	{
		mainBody->SetBodyType(Body::BodyType::Static);
		return;
	}

	//Move right
	if (input.GetKey(DIK_RIGHT))
	{
		mainBody->SetVelocity(5, mainBody->GetVelocity().y);
	}

	//move left
	if (input.GetKey(DIK_LEFT))
	{
		mainBody->SetVelocity(-5, mainBody->GetVelocity().y);

	}

	//hold-jump 
	if (input.GetKey(DIK_Z))
	{
		if (jumpTime < MAXJUMPTIME) //continue jumping if there is still jumptime
		{
			mainBody->SetVelocity(mainBody->GetVelocity().x, mainBody->GetVelocity().y + 0.3f);
			jumpTime += 0.02f;
		}
		else
		{ 
			jumpTime = 100;  //don't jump more
		}
	}
	else
	{
		jumpTime = 100; //don't jump more
	}

	//jump only if grounded
	if (input.GetKeyDown(DIK_Z) && isGrounded)
	{
		mainBody->SetVelocity(mainBody->GetVelocity().x, 6);
		isGrounded = false;
		jumpTime = 0;
	}

	//roll if possible
	if (input.GetKeyDown(DIK_DOWN) && canRoll && isGrounded && mainBody->GetVelocity().x == 0)
	{
		mainBody->SetSize(mainBody->GetSize().x, 25); //resize to rolling size
		isRolling = true;
	}

	if (!isHeadHit) // if not being hit on head, player can transform back to original size 
	{
		if (input.GetKeyDown(DIK_UP) || input.GetKeyDown(DIK_Z))
		{
			mainBody->SetSize(mainBody->GetSize().x, 60); //back to original size
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

	//looking up
	if (input.GetKey(DIK_UPARROW))
	{
		isLookingup = true;
	}
	else
	{
		isLookingup = false;
	}

	//shooting
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

	//bombing
	if (input.GetKeyDown(DIK_SPACE) && !isBombing&&canBomb&&isRolling)
	{
		bomb = new Bomb(world, &texture);
		bomb->GetMainBody()->SetPosition(this->GetPosition().x, this->GetPosition().y);
		bomb->Play();
		isBombing = true;
	}

	if (isShooting)
	{
		Fire();
	}

}

void Player::Fire()
{

	float currentTime = GetTickCount() / 1000.0f;
	if (currentTime > FIRERATE + lastShot) //don't shoot more if we have just shooted 
	{
		//instantiate bullet
		Bullet* bullet = new Bullet(world, &texture);
		Vector2 position;
		Vector2 velocity;
		if (isLookingup) //shoot up
		{
			position.x = GetPosition().x;
			position.y = GetPosition().y + GetSize().y / 2 + bullet->GetSize().y / 2;
			velocity.Set(0, BULLETSPEED);
		}
		else
		{
			if (!IsFlipX()) //shoot right
			{
				position.x = GetPosition().x + GetSize().x / 2 + bullet->GetSize().x / 2;
				position.y = GetPosition().y + 10;
				velocity.Set(BULLETSPEED, 0);
			}
			else //shoot left
			{
				position.x = GetPosition().x - GetSize().x / 2 - bullet->GetSize().x / 2;
				position.y = GetPosition().y + 10;
				velocity.Set(-BULLETSPEED, 0);
			}
		}
		//set position and velocity of bullet
		bullet->GetMainBody()->SetPosition(position.x, position.y);
		bullet->GetMainBody()->SetVelocity(velocity.x, velocity.y);

		//push to vector to easily manage these bullets
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
	if (health > 0)
	{
		//draw bullets
		for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
		{
			(*it)->Render(batch);
		}

		//draw bomb
		if (bomb != NULL)
		{
			bomb->Render(batch);
		}

		//draw player
		batch->Draw(*this);
	}
	else
	{
		if (deadTime < MAXDEADTIME)
		{
			int i = 0;
			for (std::vector<Sprite>::iterator it = deadEffect.begin(); it != deadEffect.end(); ++it)
			{
				it->SetPosition(it->GetPosition().x + 5 * cos(45 * i*Pi / 180), it->GetPosition().y + 5 * sin(45 * i*Pi / 180));
				batch->Draw(*it);
				i++;
			}
		}

	}
}


void Player::Update(float dt)
{

	if (health <= 0)
	{
		if (deadTime == -1) 
		{
			//setup for deadEffect
			for (std::vector<Sprite>::iterator it = deadEffect.begin(); it != deadEffect.end(); ++it)
			{
				it->SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y);
			}
			deadTime = 0;
		}
		else
		{
			deadTime += dt;
		}
	}


	if (beingHitTime == -1) //not being hit
	{
		//before anything else, we know that there are 3 main animations: standing, moving and jumping
		//setup these help us easily to manage animation transaction (You don't have to follow this way but this one is the easiest way I can think of
		if (isGrounded)
		{


			if (mainBody->GetVelocity().x == 0)
			{
				characterStateManager.SetCurrentAnimation(&standingAnimation); //setup main animation
			}
			else
			{
				characterStateManager.SetCurrentAnimation(&movingAnimation); //setup main animation
			}

		}
		else
		{
			characterStateManager.SetCurrentAnimation(&jumpingAnimation); //setup main animation
		}

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
	
	//update bomb
	if (bomb != NULL)
	{
		bomb->Update(dt);
		if (bomb->IsDestroyed())
		{
			delete bomb;
			bomb = NULL;
			isBombing = false;
		}

	}
	
}

void Player::OnHeadHit()
{
	isHeadHit = true;
}

void Player::OnHitRollItem()
{
	sound.PlaySoundW(itemAcquisition);
	canRoll = true;
}

void Player::OnHitBombItem()
{
	canBomb = true;
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

bool Player::IsDead()
{
	return deadTime > MAXDEADTIME;
}


Body* Player::GetMainBody()
{
	return mainBody;
}

void Player::Release()
{

	//release bullets
	for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
	{
		delete (*it);
	}

	//release bomb
	if (bomb != NULL)
	{
		delete bomb;
		bomb = NULL;
	}

}

bool Player::getisGrounded()
{
	return isGrounded;
}