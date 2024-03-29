#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"
#include "HanabiEffect.h"

#define CANNOTFIRERATE 1.5
#define MAXBULLETLIVETIME 1

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

	float stateTime; //
	

public:
	Cannon();
	~Cannon();
	void Create(World *world, Texture *texture, Cannon::Type type, int randomIndex , int x, int y);

	//used for quadtree
	void Create(World *world, Texture *texture, Cannon::Type type, int randomIndex, Body* body);

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void Destroy();

	void OnHitGround();



};

