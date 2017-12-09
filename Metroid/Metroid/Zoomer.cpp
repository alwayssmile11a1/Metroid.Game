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
	SetPosition(16 * 80, 16 * 15);
	prevCollisionDirection.x = 100.0f;
	prevCollisionDirection.y = -0.5;
	curCollisionDirection.x = 100.0f;
	curCollisionDirection.y = -0.5;

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(16 * 80, 16 * 15);
	bodyDef.size.Set(16, 14);
	body = world->CreateBody(bodyDef);
	body->categoryBits = ZOOMER_BIT;
	body->maskBits = PLAYER_BIT | PLATFORM_BIT;
	body->PutExtra(this);
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
	body->SetVelocity(0.5f, -0.5f);
	//StickToGround();
	SetRegion(zoomerAnimation.Next(dt));

}

void Zoomer::StickToGround()
{
	if (curCollisionDirection.x != 100.0f && curCollisionDirection.y != 100.0f)
	{
		body->SetVelocity(body->GetVelocity().x, -body->GetVelocity().y);
	}
	else
	{
		if (prevCollisionDirection.x != curCollisionDirection.x || prevCollisionDirection.y != curCollisionDirection.y)
		{
			if (prevCollisionDirection.x == curCollisionDirection.x && prevCollisionDirection.y != curCollisionDirection.y)
			{
				prevCollisionDirection.x = body->GetVelocity().x;
				prevCollisionDirection.y = curCollisionDirection.y;
				body->SetVelocity(-body->GetVelocity().x, body->GetVelocity().y);
			}
			else
			{
				if (prevCollisionDirection.x != curCollisionDirection.x && prevCollisionDirection.y == curCollisionDirection.y)
				{
					prevCollisionDirection.x = curCollisionDirection.x;
					prevCollisionDirection.y = -body->GetVelocity().y;
					body->SetVelocity(body->GetVelocity().x, -body->GetVelocity().y);
				}
			}
		}
		else
		{
			body->SetVelocity(body->GetVelocity().x, body->GetVelocity().y);
		}
	}
}