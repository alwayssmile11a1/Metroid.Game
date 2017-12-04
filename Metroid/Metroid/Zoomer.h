#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include<vector>
#include "CollisionBit.h"
#include "Player.h"

class Zoomer: public Sprite
{
private:
	Animation zoomerAnimation;
	Body* body;

	float stateTime;

	World* world;

	bool isDead;

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

	void Follow(Player* player);
};

