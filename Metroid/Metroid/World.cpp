#include"World.h"

World::World()
{
	this->width = 0;
	this->height = 0;
	this->dt = 0;
}

World::World(int width, int height, DWORD dt)
{
	this->width = width;
	this->height = height;
	this->dt = dt;
}

World::~World()
{
	
}