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
	SetPosition(16 * 80, 16 * 6.7);
	prevCollisionDirection.x = 100.0f;
	prevCollisionDirection.y = 50.0f;
	curCollisionDirection.x = 100.0f;
	curCollisionDirection.y = 50.0f;
	prevVelocity.x = 2.0f;
	prevVelocity.y = -0.5f;

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(16 * 80, 16 * 6.7);
	bodyDef.size.Set(16, 14);
	body = world->CreateBody(bodyDef);
	body->categoryBits = ZOOMER_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT;
	body->PutExtra(this);
	body->SetVelocity(2.0f, -0.5f);
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
	SetRegion(zoomerAnimation.Next(dt));

}

void Zoomer::SetCurCollisionDirection(Vector2 collisionDirection)
{
	curCollisionDirection = collisionDirection;
}

void Zoomer::StickToGround()
{
	if (curCollisionDirection.x != 100.0f && curCollisionDirection.y != 100.0f)
	{
		body->SetVelocity(prevVelocity.x, -prevVelocity.y);
		prevVelocity.y = -prevVelocity.y * 100;
		prevCollisionDirection.x = curCollisionDirection.x;
		prevCollisionDirection.y = 100.0f;
	}
	else
	{
		if (prevCollisionDirection.x != curCollisionDirection.x || prevCollisionDirection.y != curCollisionDirection.y)
		{
			if (prevCollisionDirection.x == curCollisionDirection.x && prevCollisionDirection.y != curCollisionDirection.y)
			{
				body->SetVelocity(-prevVelocity.x, prevVelocity.y);
				prevCollisionDirection.x = prevVelocity.x * 100;
				prevVelocity.x = -prevVelocity.x;
				prevCollisionDirection.y = curCollisionDirection.y;
			}
			else
			{
				if (prevCollisionDirection.x != curCollisionDirection.x && prevCollisionDirection.y == curCollisionDirection.y)
				{
					body->SetVelocity(prevVelocity.x, -prevVelocity.y);
					prevCollisionDirection.x = curCollisionDirection.x;
					prevCollisionDirection.y = prevVelocity.y * 100;
					prevVelocity.y = -prevVelocity.y;
				}
			}
		}
		else
		{
			body->SetVelocity(prevVelocity.x, prevVelocity.y);
		}
	}
}