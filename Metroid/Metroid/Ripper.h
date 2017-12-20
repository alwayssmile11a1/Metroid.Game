#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include<vector>
#include "CollisionBit.h"
#include "Player.h"


class Ripper : public Sprite
{

private:
	Animation ripperAnimation;
	Animation skreeHitAnimation;
	Body* body;



	float stateTime;

	World* world;

	bool isHitGround;

	bool isDead;

	Player* player;

	float hitBulletTime;

	int health;


public:
	Ripper();
	~Ripper();
	void Create(World *world, Texture *ripperTexture, int x, int y);

	void HandlePhysics(Player* player);

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitGround();

	bool IsDead();

	int GetHealth();
};
