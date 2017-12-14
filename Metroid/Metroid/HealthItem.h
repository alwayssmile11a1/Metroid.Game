#pragma once

#include "HanabiSprite.h"
#include "HanabiBody.h"
#include "HanabiWorld.h"
#include "CollisionBit.h"
class HealthItem: public Sprite
{
private:
	Body* body;

	World *world;

	Animation animation;

	bool isHitPlayer;

public:
	HealthItem();
	~HealthItem();

	void Create(World *world, Texture *itemsTexture, int x, int y);

	void Update(float dt);

	void Render(SpriteBatch *batch);

	void OnHitPlayer();

	bool IsHitPlayer();

};

