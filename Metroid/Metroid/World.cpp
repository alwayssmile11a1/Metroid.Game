#include"World.h"

World::World()
{
	bounds.setX(0);
	bounds.setY(0);
	this->dt = 0;
}

World::World(int width, int height, DWORD dt)
{
	bounds.setX(width);
	bounds.setY(height);
	this->dt = dt;
}

World::~World()
{
	
}

//All get functions
Vector2 World::getBounds()
{	
	return bounds;
}

std::vector<Object> World::getObjectsList()
{
	return objects;
}

//All set functions
void World::setBounds(Vector2 value)
{
	bounds = value;
}

void World::setDeltaTime(DWORD dt)
{
	this->dt = dt;
}

//Update world (update all the objects in this world)
void World::update(DWORD dt)
{
	for (std::vector<Object>::iterator object = objects.begin(); object !=objects.end();++object)
	{
		object->update(dt);
	}
}
void World::addObject(Object object)
{
	objects.push_back(object);
}
void World::removeObject(Object* object)
{

}
void World::removeObject(int index)
{

}