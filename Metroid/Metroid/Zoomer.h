#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include<vector>
#include "CollisionBit.h"
#include "Player.h"

class Zoomer : public Sprite
{
private:
	Animation zoomerAnimation;
	Body* body;

	float stateTime;

	World* world;

	bool isDead;
	Vector2 prevCollisionDirection;
	Vector2 curCollisionDirection;
	Vector2 prevVelocity;

	Player* player;

public:

	Zoomer();
	~Zoomer();
	void Create(World *world, Texture *skreeTexture);

	void HandlePhysics();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitPlayer();

	void OnHitGround();

	void StickToGround();

	void SetCurCollisionDirection(Vector2 collisionDirection);
};