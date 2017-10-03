#include"World.h"

World::World()
{
	bounds.setX(0);
	bounds.setY(0);
	this->dt = 0;
	objects.clear();
}

World::World(int width, int height, DWORD dt)
{
	bounds.setX(width);
	bounds.setY(height);
	this->dt = dt;
}

World::~World()
{
	for (std::vector<Object*>::iterator obj = objects.begin(); obj != objects.end(); ++obj)
	{
		delete *obj;
	}
}

World::World(const World &world)
{
	this->bounds = world.bounds;
	this->dt = world.dt;
	std::vector<Object*> vectorCopy = world.getObjectsList();
	for (std::vector<Object*>::iterator obj = vectorCopy.begin(); obj != vectorCopy.end(); ++obj)
	{
		Object * temp = new Object();
		*temp = **obj;
		this->objects.push_back(temp);
	}
}

//All get functions
Vector2 World::getBounds()
{	
	return bounds;
}

std::vector<Object*> World::getObjectsList() const
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
void World::update(DWORD dt, LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 backbuffer)
{
	for (std::vector<Object*>::iterator obj = objects.begin(); obj !=objects.end();++obj)
	{
		(*obj)->update(dt);
		(*obj)->RenderFrame(d3ddv, backbuffer, dt);
	}
}
void World::addObject(Object *object)
{
	objects.push_back(object);
}
void World::removeObject(Object* object)
{
	for (std::vector<Object*>::iterator obj = objects.begin(); obj != objects.end(); ++obj)
	{
		if ((*obj) == object)
		{
			objects.erase(obj);
			break;
		}
	}
}
void World::removeObject(int index)
{
	objects.erase(objects.begin() + index);
}