#pragma once
#include "World.h"

#define PLATFORM_BIT 1

class Platform
{
public:
	Platform();
	~Platform();
	Platform(World *world, float x, float y, float width, float height);

};

