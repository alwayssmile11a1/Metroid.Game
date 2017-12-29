#pragma once

#include "HanabiSprite.h"
#include "HanabiBody.h"
#include "HanabiWorld.h"
#include "CollisionBit.h"

class MaruMariItem: public Sprite
{
private:
	Body* body;

	World *world;

	Animation animation;

	bool isHitPlayer;

public:
	MaruMariItem();
	~MaruMariItem();

	void Create(World *world, Texture *itemsTexture, int x, int y);
	
	void Create(World *world, Texture *itemsTexture, Body*body);

	void Update(float dt);

	void OnHitPlayer();
};

