#pragma once

#include "HanabiSprite.h"
#include "HanabiBody.h"
#include "HanabiWorld.h"
#include "CollisionBit.h"

class RollAbilityItem: public Sprite
{
private:
	Body* body;

	World *world;

	Animation animation;

	bool isHitPlayer;

public:
	RollAbilityItem();
	~RollAbilityItem();

	void Create(World *world, Texture *itemsTexture, int x, int y);
	
	void Update(float dt);

	void OnHitPlayer();
};

