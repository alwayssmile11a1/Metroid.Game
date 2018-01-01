#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include<vector>
#include "CollisionBit.h"
#include "Player.h"

#define MAXHITBULLETTIME 0.05
#define MAXHITPLAYERHITTIME 0.2


class Rio : public Sprite
{

private:
	Animation rioAnimation;
	Body* body;

	World* world;

	Player* player;

	bool phase1;

	bool phase2;

	bool right;

	bool still;

	bool isHitRoof;

	bool isHitGround;

	bool isHitRight;

	bool isHitLeft;

	bool jumpCheck;

	float delayTime;
	float delayTimeDuringGame;
	
	bool isDead;
	int health;
	float hitBulletTime;
	float hitPlayerTime;

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

	//use for quadtree
	void Create(World *world, Texture *rioTexture, Body *body);

	void HandlePhysics(Player *player);

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitGround();

	void OnHitRoof();

	void OnHitLeft();

	void OnHitRight();
	
	bool IsDead();

	int GetHealth();

	void OnHitPlayer();

	void OnHitBomb();

	void OnHitBullet();
};

