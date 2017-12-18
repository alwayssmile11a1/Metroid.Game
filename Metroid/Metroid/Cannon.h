#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include<vector>
#include "CollisionBit.h"
#include "HanabiEffect.h"

#define CANNOTFIRERATE 1.5

class CannonBullet: public Sprite
{
public:
	Body * body;
};

class Cannon : public Sprite
{
public:
	enum Type { Left, Right, Top };
private:
	Animation cannonAnimation;
	Animation bulletAnimation;

	Body* body;
	World* world;

	float lastShot;

	CannonBullet cannonBullet;

	bool isBulletDestroyed;
	
	Effect bulletExplosionEffect;
	

public:
	Cannon();
	~Cannon();
	void Create(World *world, Texture *skreeTexture, Cannon::Type type, int randomIndex , int x, int y);

	void HandlePhysics();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitGround();



};

