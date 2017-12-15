#include "Bomb.h"



Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

Bomb::Bomb(World *world, Texture* texture)
{
	isDestroyed = false;
	stateTime = 0;
	this->world = world;

	//get bullet 
	TexturePacker p = TexturePacker(texture, "Resources/samusaran_packer.xml");
	animation.AddRegion(p.GetRegion("bomb"));

	this->SetRegion(*animation.GetKeyAnimation());
	SetSize(16, 16);

	//body definition
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.size.Set(16, 16);
	bodyDef.isSensor = true;

	//create body
	mainBody = world->CreateBody(bodyDef);
	mainBody->categoryBits = 0; //not collide with anything		
	mainBody->maskBits = SKREE_BIT | ZOOMER_BIT | PLAYER_BIT| BREAKABLEPLATFORM_BIT;
	mainBody->PutExtra(this);

	//effects
	explosionEffect.Create(texture);
	explosionEffect.SetSize(32, 32);

}

void Bomb::Render(SpriteBatch *batch)
{
	batch->Draw(*this);

	explosionEffect.Render(batch);
}

void Bomb::Update(float dt)
{
	stateTime += dt;

	if (mainBody->categoryBits == EXPLOSION_BIT)
	{
		if (stateTime < EXPLOSIONLIVETIME)
		{
			explosionEffect.Update(dt);
			mainBody->SetSize(mainBody->GetSize().x + 5, mainBody->GetSize().y + 5);
		}
		else
		{
			world->DestroyBody(mainBody);
			mainBody = NULL;
			isDestroyed = true;
		}
	}
	else
	{
		SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y);

		if (stateTime > BOMBLIVETIME)
		{
			mainBody->categoryBits = EXPLOSION_BIT;
			SetTexture(NULL);
			explosionEffect.SetPosition(this->GetPosition().x, this->GetPosition().y);
			explosionEffect.Play();
		}
	}

}

Body* Bomb::GetMainBody()
{
	return mainBody;
}

bool Bomb::IsDestroyed()
{
	return isDestroyed;
}

void Bomb::OnHitEnemy()
{
	stateTime = 100; //force to be dead
}

void Bomb::Play()
{
	stateTime = 0;
}