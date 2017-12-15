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
	mainBody->categoryBits = BOMB_BIT;
	mainBody->maskBits = SKREE_BIT | ZOOMER_BIT;
	mainBody->PutExtra(this);

	//effects
	explosionEffect.Create(texture);
	explosionEffect.SetSize(24, 24);

}

void Bomb::Render(SpriteBatch *batch)
{
	batch->Draw(*this);

	explosionEffect.Render(batch);
}

void Bomb::Update(float dt)
{
	stateTime += dt;

	if (mainBody == NULL)
	{
		if (stateTime < EXPLOSIONLIVETIME)
		{
			explosionEffect.Update(dt);
		}
		else
		{
			isDestroyed = true;
		}
	}
	else
	{
		SetPosition(mainBody->GetPosition().x, mainBody->GetPosition().y);

		if (stateTime > BOMBLIVETIME)
		{
			world->DestroyBody(mainBody);
			mainBody = NULL;
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