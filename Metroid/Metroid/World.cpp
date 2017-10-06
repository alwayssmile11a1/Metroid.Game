#include"World.h"

World::World()
{
	Bounds = Vector2(0, 0);
	DeltaTime = 0;
	Objects.clear();
}

World::World(int width, int height, DWORD dt)
{
	Bounds = Vector2(width, height);
	this->DeltaTime = dt;
}

World::~World()
{
	for (std::vector<Object*>::iterator obj = Objects.begin(); obj != Objects.end(); ++obj)
	{
		if (*obj != NULL)
		{
			delete *obj;
			*obj = NULL;
		}
	}
}

World::World(const World &world)
{
	this->Bounds = world.Bounds;
	this->DeltaTime = world.DeltaTime;
	std::vector<Object*> vectorCopy = world.GetObjectsList();
	for (std::vector<Object*>::iterator obj = vectorCopy.begin(); obj != vectorCopy.end(); ++obj)
	{
		Object * temp = new Object();
		*temp = **obj;
		this->Objects.push_back(temp);
	}
}

World& World::operator=(const World &world)
{
	this->Bounds = world.Bounds;
	this->DeltaTime = world.DeltaTime;
	std::vector<Object*> vectorCopy = world.GetObjectsList();
	for (std::vector<Object*>::iterator obj = vectorCopy.begin(); obj != vectorCopy.end(); ++obj)
	{
		Object * temp = new Object();
		*temp = **obj;
		this->Objects.push_back(temp);
	}
	return *this;
}

//All get functions
Vector2 World::GetBounds()
{	
	return Bounds;
}

std::vector<Object*> World::GetObjectsList() const
{
	return Objects;
}

//All set functions
void World::SetBounds(Vector2 value)
{
	Bounds = value;
}

void World::SetDeltaTime(DWORD dt)
{
	this->DeltaTime = dt;
}

//Update world (update all the objects in this world)
void World::Update(DWORD dt)
{
	for (std::vector<Object*>::iterator obj = Objects.begin(); obj != Objects.end();++obj)
	{
		(*obj)->Update(dt);
	}
}
void World::AddObject(Object *object)
{
	Objects.push_back(object);
}
void World::RemoveObject(Object* object)
{
	for (std::vector<Object*>::iterator obj = Objects.begin(); obj != Objects.end(); ++obj)
	{
		if ((*obj) == object)
		{
			Objects.erase(obj);
			break;
		}
	}
}
void World::RemoveObject(int index)
{
	Objects.erase(Objects.begin() + index);
}