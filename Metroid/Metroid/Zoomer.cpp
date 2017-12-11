#include "Zoomer.h"



Zoomer::Zoomer()
{
}


Zoomer::~Zoomer()
{
}

void Zoomer::Create(World *world, Texture *skreeTexture)
{
	this->world = world;
	TexturePacker p = TexturePacker(skreeTexture, "Resources/enemies_packer.xml");

	zoomerAnimation.AddRegion(p.GetRegion("zoomer"));
	zoomerAnimation.SetFrameInterval(0.04);

	SetRegion(zoomerAnimation.GetKeyAnimation());
	SetSize(16, 14);
	SetPosition(16 * 105, 16 * 14);
	prevVelocity.x = 0.7f;
	prevVelocity.y = -0.7f;
	prevCollisionDirection.x = NOT_COLLIDED;
	prevCollisionDirection.y = -prevVelocity.y * 100;
	curCollisionDirection.x = NOT_COLLIDED;
	curCollisionDirection.y = -prevVelocity.y * 100;

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(16 * 105, 16 * 14);
	bodyDef.size.Set(16, 14);
	body = world->CreateBody(bodyDef);
	body->categoryBits = ZOOMER_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT;
	body->PutExtra(this);
	body->SetVelocity(0.7f, -0.7f);
	cooldownAfterCollisionChange = 3;
}

void Zoomer::HandlePhysics()
{
	StickToGround();
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
	//StickToGround();
	SetRegion(zoomerAnimation.Next(dt));

}

void Zoomer::SetCurCollisionDirection(Vector2 collisionDirection)
{
	if (collisionDirection.x == prevCollisionDirection.y && collisionDirection.y == prevCollisionDirection.x)
	{
		if (prevCollisionDirection.x != NOT_COLLIDED)
		{
			curCollisionDirection.y = collisionDirection.y;
		}
		else
		{
			curCollisionDirection.x = collisionDirection.x;
		}
	}
	else
		curCollisionDirection = collisionDirection;
}

void Zoomer::StickToGround()
{
	if (curCollisionDirection.x != NOT_COLLIDED && curCollisionDirection.y != NOT_COLLIDED && cooldownAfterCollisionChange == 0)
	{
		body->SetVelocity(prevVelocity.x, -prevVelocity.y);
		prevVelocity.y = -prevVelocity.y * 100;
		prevCollisionDirection.x = curCollisionDirection.x;
		prevCollisionDirection.y = NOT_COLLIDED;
		cooldownAfterCollisionChange = 3;
	}
	else
	{
		if ((prevCollisionDirection.x != curCollisionDirection.x || prevCollisionDirection.y != curCollisionDirection.y) && cooldownAfterCollisionChange == 0)
		{
			if (prevCollisionDirection.x == curCollisionDirection.x && prevCollisionDirection.y != curCollisionDirection.y)
			{
				body->SetVelocity(-prevVelocity.x, prevVelocity.y);
				prevCollisionDirection.x = prevVelocity.x * 100;
				prevVelocity.x = -prevVelocity.x;
				prevCollisionDirection.y = curCollisionDirection.y;
				cooldownAfterCollisionChange = 3;
			}
			else
			{
				if (prevCollisionDirection.x != curCollisionDirection.x && prevCollisionDirection.y == curCollisionDirection.y)
				{
					body->SetVelocity(prevVelocity.x, -prevVelocity.y);
					prevCollisionDirection.x = curCollisionDirection.x;
					prevCollisionDirection.y = prevVelocity.y * 100;
					prevVelocity.y = -prevVelocity.y;
					cooldownAfterCollisionChange = 3;
				}
			}
		}
		else
		{
			body->SetVelocity(prevVelocity.x, prevVelocity.y);
			if (cooldownAfterCollisionChange > 0)
				cooldownAfterCollisionChange--;
		}
	}
}