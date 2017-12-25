#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include<vector>
#include "CollisionBit.h"
#include "Player.h"

#define MAXHITBULLETTIME 0.2

class Ripper : public Sprite
{

private:
	Animation ripperAnimation;

	Body* body;

	World* world;

	bool isHitGround;

	bool isDead;

	Player* player;

	float hitBulletTime;

	int health;

	Vector2 velocity;

	float pauseTime;

	CSound *isShot = NULL;
public:
	Ripper();
	~Ripper();
	void Create(World *world, Texture *ripperTexture, int x, int y);

	void HandlePhysics(Player* player);

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitGround();

	void OnHitBullet();

	void OnHitPlayer();

	void ChangeDirection();

	bool IsDead();

	int GetHealth();
};
