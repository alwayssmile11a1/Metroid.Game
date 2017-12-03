#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include<vector>
#include "CollisionBit.h"
#include "Player.h"

#define SKREELIVETIME 0.5f
#define SKREEBULLETLIVETIME 1
#define PI 3.14159265


class SkreeBullet
{
public:
	Body* body;
	Sprite sprite;
};


class Skree:public Sprite
{
private:
	Animation skreeAnimation;
	Body* body;

	std::vector<SkreeBullet> skreeBullets;

	Animation skreeBulletAnimation;

	float stateTime;

	World* world;

	bool isDead;

	Player* player;

public:
	Skree();
	~Skree();
	void Create(World *world, Texture *skreeTexture);

	void HandlePhysics();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitPlayer();

	void OnHitGround();

	void Follow(Player* player);

};

