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

//All get functions
int World::GetWidth()
{
	return width;
}
int World::GetHeight()
{
	return height;
}
std::vector<Object> World::GetObjectsList()
{
	return objects;
}

//All set functions
void World::SetWidth(int width)
{
	this->width = width;
}
void World::SetHeight(int height)
{
	this->height = height;
}
void World::SetDeltaTime(DWORD dt)
{
	this->dt = dt;
}

//Update world (update all the objects in this world)
void World::Update(DWORD dt)
{
	for (std::vector<Object>::iterator object = objects.begin(); object !=objects.end();++object)
	{
		object->Update(dt);
	}
}
void World::AddObject(Object object)
{
	objects.push_back(object);
}
void World::RemoveObject(Object* object)
{

}
void World::RemoveObject(int index)
{

}