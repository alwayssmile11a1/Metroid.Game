#pragma once
#include "HanabiSprite.h"
#include "HanabiWorld.h"
#include "CollisionBit.h"

class BombItem : public Sprite
{
private:
	Body* body;

	World *world;

	Animation animation;

	bool isHitPlayer;

public:
	BombItem();
	~BombItem();

	void Create(World *world, Texture *itemsTexture, int x, int y);

	void Update(float dt);

	void OnHitPlayer();
};


