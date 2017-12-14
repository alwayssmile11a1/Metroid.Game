#include "ExplosionEffect.h"



ExplosionEffect::ExplosionEffect()
{
}


ExplosionEffect::~ExplosionEffect()
{
}

void ExplosionEffect::Create(Texture* explosionTexture)
{
	stateTime = 0;

	TexturePacker p = TexturePacker(explosionTexture, "Resources/effects_packer.xml");

	explosionAnimation.AddRegion(p.GetRegion("explosion"));

	SetRegion(*explosionAnimation.GetKeyAnimation());
}

void ExplosionEffect::Render(SpriteBatch* batch)
{
	if (stateTime == -1) return;
	batch->Draw(*this);
}

void ExplosionEffect::Update(float dt)
{
	if (stateTime == -1) return;
	
	if (stateTime < EFFECTLIVETIME)
	{
		SetRegion(*explosionAnimation.Next(dt));
		stateTime += dt;
	}
	else
	{
		stateTime = -1;
	}

}

void ExplosionEffect::Play()
{
	stateTime = 0;
}