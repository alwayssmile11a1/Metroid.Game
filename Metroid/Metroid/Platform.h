#pragma once
#include "World.h"

#include "CollisionBit.h"

class Platform
{
public:
	Platform();
	~Platform();
	Platform(World *world, float x, float y, float width, float height);

};

