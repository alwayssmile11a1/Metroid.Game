#include "Rio.h"



Rio::Rio()
{

}


Rio::~Rio()
{
}

void Rio::Create(World *world, Texture *rioTexture, float x, float y)
{
	isHitRoof = true;
	isHitGround = false;
	isHitLeft = false;
	isHitRight = false;
	jumpCheck = true;
	health = 4;
	phase1 = true;
	phase2 = true;
	right = true;
	still = false;
	delayTime = 0.5;
	delayTimeDuringGame = 0;

	hitBulletTime = -1;

	startVelo1 = Vector2(2, -6);
	startVelo2 = Vector2(-2, -6);
	deacceleration = (float)0.05;

	midVelo1 = Vector2(2, (float)0.05);
	midVelo2 = Vector2(-2, (float)0.05);
	acceleration = (float)0.5;

	this->world = world;

	TexturePacker p = TexturePacker(rioTexture, "Resources/enemies_packer.xml");

	rioAnimation.AddRegion(p.GetRegion("rio"));
	rioAnimation.SetFrameInterval((float)0.04);

	SetRegion(*rioAnimation.GetKeyAnimation());
	SetSize(45, 40);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(45, 40);
	bodyDef.isSensor = false;
	body = world->CreateBody(bodyDef);
	body->categoryBits = RIO_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | BULLET_BIT;
	body->PutExtra(this);
}


void Rio::HandlePhysics(Player *player)
{
	if (player->getisGrounded() == true)
	{
		jumpCheck = true;
	}
	if (still)
	{
		if (delayTimeDuringGame >= delayTime)
		{
			delayTimeDuringGame = 0;
			still = false;
		}
		else
		{

		}
	}
	else
	{
		if (right == true)
		{
			if (phase1 == true)
			{
				midVelo1.Set(2, 0.05);
				if (isHitRoof)
				{
					isHitRoof = false;
				}
				if (isHitRoof == false)
				{
					body->SetVelocity(startVelo1.x, startVelo1.y);
					if (isHitGround == false) startVelo1.Set(startVelo1.x, startVelo1.y + deacceleration);
					if (isHitGround == true && player->GetPosition().x - body->GetPosition().x < 0)
					{
						right = true;
						phase1 = false;
					}
					if (player->getisGrounded() == false && jumpCheck == true && abs(player->GetPosition().x - body->GetPosition().x) < 50)
					{
						jumpCheck = false;
						right = true;
						phase1 = false;
					}
					if (isHitRight)
					{
						isHitRight = false;
						isHitLeft = false;
						right = false;
						phase2 = true;
						phase1 = false;
						startVelo2.Set(-2, -6);
					}
				}
			}
			else if (phase1 == false)
			{
				startVelo1.Set(2, -6);
				if (isHitGround == true)
				{
					isHitGround = false;
				}
				body->SetVelocity(midVelo1.x, midVelo1.y);
				midVelo1.Set(midVelo1.x, midVelo1.y + acceleration);
				if (isHitRoof == true)
				{
					still = true;
					delayTimeDuringGame = 0;
					body->SetVelocity(0, 0);
					right = false;
					phase1 = true;
				}
			}
		}
		else if (right == false)
		{
			if (phase2 == true)
			{
				midVelo2.Set(-2, (float)0.05);
				if (isHitRoof)
				{
					isHitRoof = false;
				}
				if (isHitRoof == false)
				{
					body->SetVelocity(startVelo2.x, startVelo2.y);
					if (isHitGround == false) startVelo2.Set(startVelo2.x, startVelo2.y + deacceleration);
					if (isHitGround == true && player->GetPosition().x - body->GetPosition().x > 0)
					{
						right = false;
						phase2 = false;
					}
					if (player->getisGrounded() == false && jumpCheck == true && abs(player->GetPosition().x - body->GetPosition().x) < 50)
					{
						jumpCheck = false;
						right = false;
						phase2 = false;
					}
					if (isHitLeft)
					{
						isHitLeft = false;
						isHitRight = false;
						right = true;
						phase1 = true;
						phase2 = false;
						startVelo1.Set(2, -6);
					}
				}
			}
			else if (phase2 == false)
			{
				startVelo2.Set(-2, -6);
				if (isHitGround == true)
				{
					isHitGround = false;
				}
				body->SetVelocity(midVelo2.x, midVelo2.y);
				midVelo2.Set(midVelo2.x, midVelo2.y + acceleration);
				if (isHitRoof == true)
				{
					still = true;
					delayTimeDuringGame = 0;
					body->SetVelocity(0, 0);
					phase2 = true;
					right = true;
				}
			}
		}
	}
}

void Rio::Render(SpriteBatch *batch)
{
	if (isDead)
		return;
	batch->Draw(*this);
}

void Rio::Update(float dt)
{
	if (isDead) return;

	if (health <= 0)
	{
		isDead = true;
		world->DestroyBody(body);
		return;
	}
	
	if (hitBulletTime == -1) //-1 means not being hit by bullet
	{
		delayTimeDuringGame += dt;
		SetRegion(*rioAnimation.Next(dt));
	}
	else
	{
		if (hitBulletTime < MAXHITBULLETTIME)
		{
			
			hitBulletTime += dt;
		}
		else
		{
			hitBulletTime = -1;
			body->SetBodyType(Body::BodyType::Kinematic);
		}
	}

	if (hitPlayerTime != -1)
	{
		if (hitPlayerTime < MAXHITPLAYERHITTIME)
		{
			hitPlayerTime += dt;
		}
		else
		{
			hitPlayerTime = -1;
			body->maskBits = PLAYER_BIT | PLATFORM_BIT | BULLET_BIT | EXPLOSION_BIT | BREAKABLEPLATFORM_BIT;
		}
	}

	if (body != NULL)
		this->SetPosition(body->GetPosition().x, body->GetPosition().y);
}


void Rio::OnHitGround()
{
	isHitGround = true;
}


void Rio::OnHitRoof()
{
	isHitRoof = true;
}

void Rio::OnHitLeft()
{
	isHitLeft = true;
}

void Rio::OnHitRight()
{
	isHitRight = true;
}

bool Rio::IsDead()
{
	return isDead;
}

int Rio::GetHealth()
{
	return health;
}

void Rio::OnHitPlayer()
{
	hitPlayerTime = 0;
	body->maskBits = PLATFORM_BIT | BULLET_BIT | BREAKABLEPLATFORM_BIT | EXPLOSION_BIT;
}

void Rio::OnHitBullet()
{
	if (hitBulletTime != -1) return;
	health--;
	hitBulletTime = 0;
	//stop this body a little bit 
	body->SetBodyType(Body::BodyType::Static);
}

void Rio::OnHitBomb()
{
	health -= 10;
	hitBulletTime = 0;
	//stop this body a little bit 
	body->SetBodyType(Body::BodyType::Static);
}