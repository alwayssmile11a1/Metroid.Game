#pragma once
#include "HanabiWorld.h"

#include "CollisionBit.h"
#include "HanabiMap.h"

class BreakablePlatform:public Sprite
{
private:
	TMXMap* map;
	Body* body;

	int health;

public:
	BreakablePlatform();
	~BreakablePlatform();
	BreakablePlatform(World *world,TMXMap* map , float x, float y, float width, float height);

	void OnHitBomb();
	void OnHitBullet();
};

