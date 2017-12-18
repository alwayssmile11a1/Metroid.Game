#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include<vector>
#include "CollisionBit.h"


#define CANNOTFIRERATE 0.3

class Cannon : public Sprite
{

private:
	Animation cannonAnimation;
	Animation bulletAnimation;

	Body* body;
	World* world;

	float lastShot;



public:
	Cannon();
	~Cannon();
	void Create(World *world, Texture *skreeTexture, int x, int y);

	void HandlePhysics();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitBullet();

	void OnHitBomb();


};

