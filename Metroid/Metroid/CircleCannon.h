#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"
#include "Player.h"

#define CANNOTFIRERATE 2
#define CIRCLEBULLETLIVETIME 3

class CircleCannonBullet : public Sprite
{
public:
	Body * body;
};

class CircleCannon : public Sprite
{
private:
	Animation bulletAnimation;

	Body* body;
	World* world;

	float lastShot;

	CircleCannonBullet cannonBullet;

	bool isBulletDestroyed;

	float stateTime;

	Player* player;

public:
	CircleCannon();
	~CircleCannon();
	void Create(World *world, Texture *texture, Player* player, int x, int y);

	void HandlePhysics();

	void Render(SpriteBatch *batch);

	void Update(float dt);

};

