#include "Zoomer.h"



Zoomer::Zoomer()
{
}


Zoomer::~Zoomer()
{
}

void Zoomer::Create(World *world, Texture *zoomerTexture, float x, float y, bool Direction)
{
	this->world = world;
	TexturePacker p = TexturePacker(zoomerTexture, "Resources/enemies_packer.xml");

	zoomerAnimation.AddRegion(p.GetRegion("zoomer"));
	zoomerAnimation.SetFrameInterval(0.04);

	SetRegion(*zoomerAnimation.GetKeyAnimation());
	SetSize(25, 25);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(25, 25);
	body = world->CreateBody(bodyDef);
	body->categoryBits = ZOOMER_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | BULLET_BIT | BREAKABLEPLATFORM_BIT| DOOR_BIT;
	body->PutExtra(this);

	prevCollisionDirection.x = NOT_COLLIDED;
	prevCollisionDirection.y = -prevVelocity.y * 100;
	curCollisionDirection.x = NOT_COLLIDED;
	curCollisionDirection.y = -prevVelocity.y * 100;

	//set up intial velocity/direction
	if (Direction)
	{
		prevVelocity.x = 0.7f;
		prevVelocity.y = -0.7f;

		body->SetVelocity(0.7f, -0.7f);
	}
	else
	{
		prevVelocity.x = -0.7f;
		prevVelocity.y = -0.7f;

		body->SetVelocity(-0.7f, -0.7f);
	}
	initalDirection = Direction;
	cooldownAfterCollisionChange = 3;
	health = 2;
	hitBulletTime = -1;
}

void Zoomer::Create(World *world, Texture *zoomerTexture, Body* body, bool Direction)
{
	this->world = world;
	TexturePacker p = TexturePacker(zoomerTexture, "Resources/enemies_packer.xml");

	zoomerAnimation.AddRegion(p.GetRegion("zoomer"));
	zoomerAnimation.SetFrameInterval(0.04);

	SetRegion(*zoomerAnimation.GetKeyAnimation());
	SetSize(25, 25);
	SetPosition(body->GetPosition().x, body->GetPosition().y);

	//setup body
	this->body = body;
	body->SetBodyType(Body::BodyType::Kinematic);
	body->SetSize(25, 25);
	body->categoryBits = ZOOMER_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT | BULLET_BIT | BREAKABLEPLATFORM_BIT|DOOR_BIT;
	body->PutExtra(this);

	prevCollisionDirection.x = NOT_COLLIDED;
	prevCollisionDirection.y = -prevVelocity.y * 100;
	curCollisionDirection.x = NOT_COLLIDED;
	curCollisionDirection.y = -prevVelocity.y * 100;

	//set up intial velocity/direction
	if (Direction)
	{
		prevVelocity.x = 0.7f;
		prevVelocity.y = -0.7f;

		body->SetVelocity(0.7f, -0.7f);
	}
	else
	{
		prevVelocity.x = -0.7f;
		prevVelocity.y = -0.7f;

		body->SetVelocity(-0.7f, -0.7f);
	}
	initalDirection = Direction;
	cooldownAfterCollisionChange = 3;
	health = 2;
	hitBulletTime = -1;
}

////void Zoomer::HandlePhysics()
////{
////
////}

void Zoomer::Render(SpriteBatch *batch)
{
	if (isDead)
		return;

	batch->Draw(*this);
}

void Zoomer::Update(float dt, Camera *cam)
{
	if (body->GetPosition().x > cam->GetPosition().x - screenWidth / 2 && body->GetPosition().x < cam->GetPosition().x + screenWidth / 2
		&&
		(body->GetPosition().y - body->GetSize().y / 2 - 5) < (cam->GetPosition().y + screenHeight / 2) && (body->GetPosition().y + body->GetSize().y / 2 + 5) > (cam->GetPosition().y - screenHeight / 2)) {
		outsideOfCamera = false;
		body->SetBodyType(Body::BodyType::Kinematic);
		if (isDead) return;

		if (health <= 0)
		{
			isDead = true;
			world->DestroyBody(body);
			return;
		}

		if (hitBulletTime == -1) //-1 means not being hit by bullet
		{
			SetRegion(*zoomerAnimation.Next(dt));
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

		//set sprite position
		if (body != NULL)
			this->SetPosition(body->GetPosition().x, body->GetPosition().y);

		//body->SetVelocity(0.5f, -0.5f);
		if (body->GetBodyType() != Body::BodyType::Static)
		{
			StickToGround();
		}
	}
	else {
		body->SetBodyType(Body::BodyType::Static);
		outsideOfCamera = true;
	}
}

void Zoomer::SetCurCollisionDirection(Vector2 collisionDirection, int source)
{
	if (!outsideOfCamera) {
		switch (source)
		{

		case 0:
			if (abs(collisionDirection.x) == abs(prevCollisionDirection.y) && abs(collisionDirection.y) == abs(prevCollisionDirection.x))
			{
				if (prevCollisionDirection.x != NOT_COLLIDED)
				{
					curCollisionDirection.y = collisionDirection.y;
				}
				else
				{
					curCollisionDirection.x = collisionDirection.x;
				}
				prevSource = 0;
			}
			else
			{
				curCollisionDirection = collisionDirection;
				prevCollisionDirection = curCollisionDirection;
				prevSource = 0;
			}
			break;

		case 1:
			curCollisionDirection = collisionDirection;
			prevSource = 1;
			break;

		case 2:
			prevSource = 1;
			cooldownAfterCollisionChange = 3;
			break;
		}
	}
}

void Zoomer::StickToGround()
{

	if (curCollisionDirection.x != NOT_COLLIDED && curCollisionDirection.y != NOT_COLLIDED && cooldownAfterCollisionChange == 0)
	{
		if (prevCollisionDirection.x == NOT_COLLIDED)
		{
			body->SetVelocity(prevVelocity.x, -prevVelocity.y);

			if (prevVelocity.x < 0)
			{
				if (prevVelocity.y < 0)
				{
					SetRotation(GetRotation() + 90);
				}
				else
				{
					SetRotation(GetRotation() - 90);
				}				
			}
			else
			{
				if (prevVelocity.y < 0)
				{
					SetRotation(GetRotation() - 90);
				}
				else
				{
					SetRotation(GetRotation() + 90);
				}
			}

			prevVelocity.y = -prevVelocity.y;
			prevCollisionDirection.x = curCollisionDirection.x;
			prevCollisionDirection.y = NOT_COLLIDED;
		}
		else
		{
			body->SetVelocity(-prevVelocity.x, prevVelocity.y);

			if (prevVelocity.x < 0)
			{
				if (prevVelocity.y < 0)
				{
					SetRotation(GetRotation() - 90);
				}
				else
				{
					SetRotation(GetRotation() + 90);
				}
			}
			else
			{
				if (prevVelocity.y < 0)
				{
					SetRotation(GetRotation() + 90);
				}
				else
				{
					SetRotation(GetRotation() - 90);
				}
			}

			prevVelocity.x = -prevVelocity.x;
			prevCollisionDirection.y = curCollisionDirection.y;
			prevCollisionDirection.x = NOT_COLLIDED;
		}

		cooldownAfterCollisionChange = 3;
	}
	else
	{
		//(prevCollisionDirection.x != curCollisionDirection.x || prevCollisionDirection.y != curCollisionDirection.y) && cooldownAfterCollisionChange == 0
		if (prevSource == -1 && cooldownAfterCollisionChange == 0)
		{
			//prevCollisionDirection.x == curCollisionDirection.x && prevCollisionDirection.y != curCollisionDirection.y
			if (prevCollisionDirection.x == NOT_COLLIDED)
			{
				body->SetVelocity(-prevVelocity.x, prevVelocity.y);
				prevCollisionDirection.x = prevVelocity.x * 100;
				prevVelocity.x = -prevVelocity.x;
				//prevCollisionDirection.y = curCollisionDirection.y;
				prevCollisionDirection.y = NOT_COLLIDED;
				cooldownAfterCollisionChange = 3;
				prevSource = -1;
			}
			else
			{
				//prevCollisionDirection.x != curCollisionDirection.x && prevCollisionDirection.y == curCollisionDirection.y
				if (prevCollisionDirection.y == NOT_COLLIDED)
				{
					body->SetVelocity(prevVelocity.x, -prevVelocity.y);
					prevCollisionDirection.x = NOT_COLLIDED;
					prevCollisionDirection.y = prevVelocity.y * 100;
					prevVelocity.y = -prevVelocity.y;
					cooldownAfterCollisionChange = 3;
					prevSource = -1;
				}
			}

			if (initalDirection)
				SetRotation(GetRotation() + 90);
			else
				SetRotation(GetRotation() - 90);
		}
		else
		{
			body->SetVelocity(prevVelocity.x, prevVelocity.y);
			if (cooldownAfterCollisionChange > 0)
				cooldownAfterCollisionChange--;
			prevSource = -1;
		}
	}
}

void Zoomer::OnHitBullet()
{
	if (hitBulletTime != -1) return;
	health--;
	hitBulletTime = 0;
	//stop this body a little bit 
	body->SetBodyType(Body::BodyType::Static);
}

void Zoomer::OnHitBomb()
{
	health-=10;
	hitBulletTime = 0;
	//stop this body a little bit 
	body->SetBodyType(Body::BodyType::Static);
}

int Zoomer::GetHealth()
{
	return health;
}

void Zoomer::OnHitPlayer()
{
	hitPlayerTime = 0;
	prevSource = 1;
	cooldownAfterCollisionChange = 2;
	body->maskBits = PLATFORM_BIT | BULLET_BIT | BREAKABLEPLATFORM_BIT | EXPLOSION_BIT;
}