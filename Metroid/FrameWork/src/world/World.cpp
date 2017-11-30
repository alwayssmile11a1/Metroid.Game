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

//World::World(const World &world)
//{
//	this->_Gravity = world._Gravity;
//	this->_Bodies = world._Bodies;
//	_DebugSquareTexture = world._DebugSquareTexture;
//	/*std::vector<Object*> vectorCopy = world.GetObjectsList();
//	for (std::vector<Object*>::iterator obj = vectorCopy.begin(); obj != vectorCopy.end(); ++obj)
//	{
//		Object * temp = new Object();
//		*temp = **obj;
//		this->Objects.push_back(temp);
//	}*/
//}
//
//World& World::operator=(const World &world)
//{
//	this->_Gravity = world._Gravity;
//	this->_Bodies = world._Bodies;
//	_DebugSquareTexture = world._DebugSquareTexture;
//	//std::vector<Object*> vectorCopy = world.GetObjectsList();
//	//for (std::vector<Object*>::iterator obj = vectorCopy.begin(); obj != vectorCopy.end(); ++obj)
//	//{
//	//	Object * temp = new Object();
//	//	*temp = **obj;
//	//	this->Objects.push_back(temp);
//	//}
//	return *this;
//}

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
	collision.SetContactListener(_Listener);

	for (std::vector<Body*>::iterator body1 = _Bodies.begin(); body1 != _Bodies.end(); ++body1)
	{
		if ((*body1)->GetBodyType() == Body::BodyType::Static)
		{
			(*body1)->Next(dt, false, false);
			continue;
		}


		//calculate actual velocity
		(*body1)->CalculateActualVelocity(dt, _Gravity);

		//get broadphase rect 
		RECT broadphaseRect = collision.GetBroadphaseRect(*body1, dt);

		bool moveX = true, moveY = true;
		
		for (std::vector<Body*>::iterator body2 = _Bodies.begin(); body2 != _Bodies.end(); ++body2)
		{
			if ((*body1) == (*body2) || (*body2)->IsSensor() == true) continue;

			bool collide = ((*body1)->maskBits & (*body2)->categoryBits) != 0 && ((*body1)->categoryBits & (*body2)->maskBits) != 0;

			if (!collide) continue;

			//get static rect 
			RECT staticRect = collision.GetRECT(*body2);

			//check overlaying broadphase
			if (collision.IsOverlayingBroadphaseRect(broadphaseRect, staticRect))
			{
				if (collision.IsColliding(*body1, *body2, dt))
				{
					collision.PerformCollision(*body1, *body2, dt, 0, moveX, moveY);
				}
			}
		

			if (collision.IsOverlaying(*body1, *body2))
			{
				collision.PerformOverlaying(*body1, *body2, moveX, moveY);
			}

			collision.Reset();
		}

		(*body1)->Next(dt, moveX, moveY);
		
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

void World::SetContactListener(WorldContactListener *listener)
{
	_Listener = listener;
}

void World::RemoveBody(Body* body)
{

	std::vector<Body*>::iterator it = std::find(_Bodies.begin(), _Bodies.end(), body);
	if (it != _Bodies.end())
	{
		_Bodies.erase(it);
	}

}
void World::RemoveBody(int index)
{
	_Bodies.erase(_Bodies.begin() + index);
}

void World::RenderBodiesDebug(SpriteBatch *batch)
{
	
	for (std::vector<Body*>::iterator bo = _Bodies.begin(); bo != _Bodies.end(); ++bo)
	{
		float x = (*bo)->GetPosition().x;
		float y = (*bo)->GetPosition().y;
		float width = (*bo)->GetSize().x;
		float height = (*bo)->GetSize().y;

		//batch.Draw(_DebugSquareTexture, x, y, 0, 0, _DebugSquareTexture.GetImageSize().x, _DebugSquareTexture.GetImageSize().y, width, height);
		batch->DrawSquare(x, y, width, height, D3DCOLOR_ARGB(255, 0, 128, 0));
	}
}
