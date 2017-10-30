#include"World.h"

World::World()
{
	_Gravity = 9.8f;
	_Bodies.clear();
}

World::World(float gravity)
{
	_Gravity = gravity;
	_Bodies.clear();
}

World::~World()
{
	//for (std::vector<Body*>::iterator obj = _Bodies.begin(); obj != _Bodies.end(); ++obj)
	//{
	//	//just for sure
	//	if (*obj != NULL )
	//	{
	//		(*obj)->~Body();
	//		(*obj) = NULL;
	//		//delete *obj;
	//	}
	//}
}

World::World(const World &world)
{
	this->_Gravity = world._Gravity;
	this->_Bodies = world._Bodies;
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
	this->_Gravity = world._Gravity;
	this->_Bodies = world._Bodies;
	//std::vector<Object*> vectorCopy = world.GetObjectsList();
	//for (std::vector<Object*>::iterator obj = vectorCopy.begin(); obj != vectorCopy.end(); ++obj)
	//{
	//	Object * temp = new Object();
	//	*temp = **obj;
	//	this->Objects.push_back(temp);
	//}
	return *this;
}

std::vector<Body*> World::GetBodysList() const
{
	return _Bodies;
}

//All set functions
void World::SetGravity(float gravity)
{
	_Gravity = gravity;
}

//Update world (update all the objects in this world)
void World::Update(float dt)
{
	//???????????????????
}
void World::AddBody(Body *body)
{
	_Bodies.push_back(body);
}
void World::RemoveBody(Body* body)
{
	for (std::vector<Body*>::iterator bo = _Bodies.begin(); bo != _Bodies.end(); ++bo)
	{
		if ((*bo) == body)
		{
			_Bodies.erase(bo);
			break;
		}
	}
}
void World::RemoveBody(int index)
{
	_Bodies.erase(_Bodies.begin() + index);
}