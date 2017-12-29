#pragma once
#include "HanabiWorld.h"

#include "CollisionBit.h"

class Platform
{
public:
	Platform();
	~Platform();
	Platform(World *world, float x, float y, float width, float height);

	//used for quadtree
	Platform(Body* body);

};

