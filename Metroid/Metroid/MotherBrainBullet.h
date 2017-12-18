#pragma once
#include"HanabiWorld.h"
#include "CollisionBit.h"
#include "HanabiSprite.h"
#define BULLETLIVETIME 0.2f
#define BULLETSPEED 5.0f

class MotherBrainBullet : public Sprite
{
private:
	Body * mainBody;
	float stateTime;
	World *world;
	bool isDestroyed;
public:
	MotherBrainBullet();
	~MotherBrainBullet();

	MotherBrainBullet(World *world, Texture* texture);

	void Render(SpriteBatch *batch);
	void Update(float dt);
	//void Release();

	bool IsDestroyed();

	float GetBulletSpeed();

	Body* GetMainBody();

	void OnHitEnemy();
};

