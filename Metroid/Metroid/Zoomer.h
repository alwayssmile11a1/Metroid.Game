#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include<vector>
#include "CollisionBit.h"
#include "Player.h"

#define NOT_COLLIDED 10000.0f
#define MAXHITBULLETTIME 0.2
#define MAXHITPLAYERHITTIME 0.3

class Zoomer : public Sprite
{
private:
	Animation zoomerAnimation;
	Body* body;

	World* world;

	bool isDead;
	int health;
	float hitBulletTime;
	float hitPlayerTime;

	Vector2 prevCollisionDirection;
	Vector2 curCollisionDirection;
	Vector2 prevVelocity;

	// Zoomer will continue to move in the same direction if on cooldown
	int cooldownAfterCollisionChange;

	// Keeps track of where the curCollisionDirection was being set from
	// Either from OnCollisionEnter or OnColliding
	int prevSource;

	Player* player;

public:

	Zoomer();
	~Zoomer();

	//
	void Create(World *world, Texture *zoomerTexture, float x, float y, bool initalDirection);

	void HandlePhysics();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitBullet();

	void OnHitBomb();

	void OnHitPlayer();

	void StickToGround();

	void SetCurCollisionDirection(Vector2 collisionDirection, int source);
};