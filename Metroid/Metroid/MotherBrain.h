#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"



class MotherBrain : public Sprite
{

private:
	Animation animation;
	Animation weakAnimation;
	Body* body;
	World* world;

	int health;


public:
	MotherBrain();
	~MotherBrain();
	void Create(World *world, Texture *texture, int x, int y);

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitBullet();

	void OnHitBomb();

	bool IsDead();

};

