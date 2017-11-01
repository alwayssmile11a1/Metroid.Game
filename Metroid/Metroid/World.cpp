#include"World.h"

World::World()
{
	_Gravity = 9.8f;
	_Bodies.clear();
	//_DebugSquareTexture = Texture("System/debugsquare.png");
}

World::World(float gravity)
{
	_Gravity = gravity;
	_Bodies.clear();
	if (_DebugSquareTexture.GetImage() == NULL)
	{
		_DebugSquareTexture = Texture("System/debugsquare.png");
	}
}

World::~World()
{
	//if (_DebugSquareTexture != NULL)
	//{
	//	delete _DebugSquareTexture;
	//	_DebugSquareTexture = NULL;
	//}

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
	_DebugSquareTexture = world._DebugSquareTexture;
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
	_DebugSquareTexture = world._DebugSquareTexture;
	//std::vector<Object*> vectorCopy = world.GetObjectsList();
	//for (std::vector<Object*>::iterator obj = vectorCopy.begin(); obj != vectorCopy.end(); ++obj)
	//{
	//	Object * temp = new Object();
	//	*temp = **obj;
	//	this->Objects.push_back(temp);
	//}
	return *this;
}

const std::vector<Body*>& World::GetBodysList() const
{
	return _Bodies;
}

void World::SetGravity(float gravity)
{
	_Gravity = gravity;
}

void World::Update(float dt)
{
	//Check collision
	Collision collision;

	for (std::vector<Body*>::iterator body1 = _Bodies.begin(); body1 != _Bodies.end(); ++body1)
	{
		bool doNextAction = true;

		for (std::vector<Body*>::iterator body2 = _Bodies.begin(); body2 != _Bodies.end(); ++body2)
		{
			if ((*body1) == (*body2) || (*body1)->GetBodyType()==Body::BodyType::Static) continue;

			if (collision.checkCollision(**body1, **body2, dt, 0))
			{
				doNextAction = false;
			}
		}

		if (doNextAction)
		{
			(*body1)->Next(dt);
		}
		
	}


}
void World::AddBody(Body *body)
{
	_Bodies.push_back(body);
}

void World::AddBody(const std::vector<Body*> &bodies)
{
	_Bodies.insert(_Bodies.end(), bodies.begin(),bodies.end());
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

void World::RenderBodiesDebug(SpriteBatch &batch)
{
	if (_DebugSquareTexture.GetImage() == NULL)
	{
		_DebugSquareTexture = Texture("System/debugsquare.png");
	}

	for (std::vector<Body*>::iterator bo = _Bodies.begin(); bo != _Bodies.end(); ++bo)
	{
		float x = (*bo)->GetPosition().x;
		float y = (*bo)->GetPosition().y;
		float width = (*bo)->GetSize().x;
		float height = (*bo)->GetSize().y;

		batch.Draw(_DebugSquareTexture, x, y, 0, 0, _DebugSquareTexture.GetImageSize().x, _DebugSquareTexture.GetImageSize().y, width, height);
	}
}