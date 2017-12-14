#pragma once
#include "HanabiSprite.h"


#define EFFECTLIVETIME 0.2
class ExplosionEffect:public Sprite
{
private:
	Animation explosionAnimation;

	float stateTime;

public:
	ExplosionEffect();
	~ExplosionEffect();
	
	void Create(Texture* explosionTexture);

	void Update(float dt);

	void Render(SpriteBatch *batch);

	void Play();
};

