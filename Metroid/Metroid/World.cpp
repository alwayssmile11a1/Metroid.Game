#include"World.h"

World::World()
{
	_Bounds = Vector2(0, 0);
	_DeltaTime = 0;
	_Objects.clear();
}

World::World(int width, int height, DWORD dt)
{
	_Bounds = Vector2(width, height);
	_DeltaTime = dt;
}

World::~World()
{
	for (std::vector<Object*>::iterator obj = _Objects.begin(); obj != _Objects.end(); ++obj)
	{
		//just for sure
		if (*obj != NULL )
		{
			(*obj)->~Object();
			(*obj) = NULL;
			//delete *obj;
		}
	}
}

World::World(const World &world)
{
	this->_Bounds = world._Bounds;
	this->_DeltaTime = world._DeltaTime;
	this->_Objects = world._Objects;
	/*std::vector<Object*> vectorCopy = world.GetObjectsList();
	for (std::vector<Object*>::iterator obj = vectorCopy.begin(); obj != vectorCopy.end(); ++obj)
	{
		Object * temp = new Object();
		*temp = **obj;
		this->Objects.push_back(temp);
	}*/
}

World& World::operator=(const World &world)
{
	this->_Bounds = world._Bounds;
	this->_DeltaTime = world._DeltaTime;
	this->_Objects = world._Objects;
	//std::vector<Object*> vectorCopy = world.GetObjectsList();
	//for (std::vector<Object*>::iterator obj = vectorCopy.begin(); obj != vectorCopy.end(); ++obj)
	//{
	//	Object * temp = new Object();
	//	*temp = **obj;
	//	this->Objects.push_back(temp);
	//}
	return *this;
}

//All get functions
Vector2 World::GetBounds()
{	
	return _Bounds;
}

std::vector<Object*> World::GetObjectsList() const
{
	return _Objects;
}

//All set functions
void World::SetBounds(const Vector2 &value)
{
	_Bounds = value;
}

void World::SetDeltaTime(DWORD dt)
{
	this->_DeltaTime = dt;
}

//Update world (update all the objects in this world)
void World::Update(DWORD dt)
{
	for (std::vector<Object*>::iterator obj = _Objects.begin(); obj != _Objects.end();++obj)
	{
		(*obj)->Update(dt);
	}
}
void World::AddObject(Object *object)
{
	_Objects.push_back(object);
}
void World::RemoveObject(Object* object)
{
	for (std::vector<Object*>::iterator obj = _Objects.begin(); obj != _Objects.end(); ++obj)
	{
		if ((*obj) == object)
		{
			_Objects.erase(obj);
			break;
		}
	}
}
void World::RemoveObject(int index)
{
	_Objects.erase(_Objects.begin() + index);
}