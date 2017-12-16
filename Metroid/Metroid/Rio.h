#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include<vector>
#include "CollisionBit.h"
#include "Player.h"

#define SKREELIVETIMEAFTERGROUND 0.5f
#define SKREEBULLETLIVETIME 1
#define MAXHITBULLETTIME 0.2
#define PI 3.14159265


class Rio : public Sprite
{

private:
	Animation rioAnimation;
	Body* body;

	World* world;

	Player* player;

	float roofTime;

	bool phase1;

	bool phase2;

	bool right;

	bool isHitRoof;

	bool isHitGround;

	bool isDead;

	int health;

	Vector2 startVelo1;
	Vector2 startVelo2;

	float deacceleration;

	Vector2 midVelo1;
	Vector2 midVelo2;

	float acceleration;

public:
	Rio();
	~Rio();
	void Create(World *world, Texture *rioTexture, float x, float y);

	void HandlePhysics(Player *player);

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitGround();

	void OnHitRoof();

	bool IsDead();

	int GetHealth();
};

