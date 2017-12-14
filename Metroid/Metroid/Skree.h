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


class SkreeBullet
{
public:
	Body* body;
	Sprite sprite;
};


class Skree: public Sprite
{

private:
	Animation skreeAnimation;
	Animation skreeHitAnimation;
	Body* body;

	std::vector<SkreeBullet> skreeBullets;

	Animation skreeBulletAnimation;

	float stateTime;

	World* world;

	bool isHitGround;

	bool isDead;

	Player* player;

	float hitBulletTime;

	float health;


public:
	Skree();
	~Skree();
	void Create(World *world, Texture *skreeTexture, int x, int y);

	void HandlePhysics(Player* player);

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitGround();

	void OnHitBullet();

	bool IsDead();
};

