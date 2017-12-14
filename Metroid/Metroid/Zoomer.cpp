#include "Zoomer.h"



Zoomer::Zoomer()
{
}


Zoomer::~Zoomer()
{
}

void Zoomer::Create(World *world, Texture *zoomerTexture, float x, float y)
{
	this->world = world;
	TexturePacker p = TexturePacker(zoomerTexture, "Resources/enemies_packer.xml");

	zoomerAnimation.AddRegion(p.GetRegion("zoomer"));
	zoomerAnimation.SetFrameInterval(0.04);

	SetRegion(*zoomerAnimation.GetKeyAnimation());
	SetSize(25, 25);
	SetPosition(x, y);
	prevVelocity.x = 0.7f;
	prevVelocity.y = -0.7f;
	prevCollisionDirection.x = NOT_COLLIDED;
	prevCollisionDirection.y = -prevVelocity.y * 100;
	curCollisionDirection.x = NOT_COLLIDED;
	curCollisionDirection.y = -prevVelocity.y * 100;

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(25, 25);
	body = world->CreateBody(bodyDef);
	body->categoryBits = ZOOMER_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT|BULLET_BIT;
	body->PutExtra(this);
	body->SetVelocity(0.7f, -0.7f);
	cooldownAfterCollisionChange = 3;
}

void Zoomer::HandlePhysics()
{

}

void Zoomer::Render(SpriteBatch *batch)
{
	batch->Draw(*this);
}

void Zoomer::Update(float dt)
{

	//set sprite position
	this->SetPosition(body->GetPosition().x, body->GetPosition().y);
	//body->SetVelocity(0.5f, -0.5f);
	StickToGround();
	SetRegion(*zoomerAnimation.Next(dt));

}

void Zoomer::SetCurCollisionDirection(Vector2 collisionDirection, int source)
{
	if (source == 0)
	{
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
			prevSource = 0;
		}
	}
	else
	{
		curCollisionDirection = collisionDirection;
		prevSource = 1;
	}
}

void Zoomer::StickToGround()
{
	if (curCollisionDirection.x != NOT_COLLIDED && curCollisionDirection.y != NOT_COLLIDED && cooldownAfterCollisionChange == 0)
	{
		body->SetVelocity(prevVelocity.x, -prevVelocity.y);
		prevVelocity.y = -prevVelocity.y;
		prevCollisionDirection.x = curCollisionDirection.x;
		prevCollisionDirection.y = NOT_COLLIDED;
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