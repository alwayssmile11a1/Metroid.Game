#pragma once

#include"HanabiWorld.h"
#include "CollisionBit.h"
#include "HanabiSprite.h"
#include "ExplosionEffect.h"

#define BOMBLIVETIME 0.6
#define EXPLOSIONLIVETIME 0.9

class Bomb : public Sprite
{
private:
	Body *mainBody;
	float stateTime;
	World *world;
	bool isDestroyed;

	ExplosionEffect explosionEffect;

	Animation animation;




public:
	Bomb();
	~Bomb();

	Bomb(World *world, Texture* texture);

	void Render(SpriteBatch *batch);
	void Update(float dt);
	//void Release();

	bool IsDestroyed();

	Body* GetMainBody();

	void OnHitEnemy();

	void Play();

};

