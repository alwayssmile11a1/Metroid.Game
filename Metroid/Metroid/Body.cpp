#include "Body.h"

Body::Body()
{
	_Size.Set(0, 0);
	_Velocity.Set(0, 0);
	_Position.Set(0, 0);
	_Mass = 1;
	_LinearDrag.Set(1, 1);
	_TotalVelocity.Set(0, 0);
	_BodyType = BodyType::Static;
}
Body::Body(float x, float y, float width, float height, float vx, float vy)
{
	_Size.Set(width, height);
	_Velocity.Set(vx, vy);
	_Position.Set(x, y);
	_Mass = 1;
	_LinearDrag.Set(1, 1);
	_TotalVelocity.Set(0, 0);
	_BodyType = BodyType::Static;
}
Body::~Body()
{

}

void Body::SetVelocity(float vx, float vy)
{
	_Velocity.Set(vx, vy);
}
void Body::SetSize(float width, float height)
{
	_Size.Set(width, height);
}
void Body::SetPosition(float x, float y)
{
	_Position.Set(x, y);
}

const Vector2& Body::GetVelocity() const
{
	return _Velocity;
}
const Vector2& Body::GetSize() const
{
	return _Size;
}
const Vector2& Body::GetPosition() const
{
	return _Position;
}

void Body::Next(float dt, bool moveX, bool moveY)
{

	if (_BodyType == BodyType::Static)
	{
		_TotalVelocity.Set(0, 0);
		return;
	}

	//Set body to the next position
	if (moveX)
	{
		_Position.Set(_Position.x + GetTotalVelocity(dt).x*dt, _Position.y);
	}

	if (moveY)
	{
		_Position.Set(_Position.x, _Position.y + GetTotalVelocity(dt).y*dt);

	}


	//_Velocity.x = _Velocity.x * 100;
	_Velocity.y += -9.8 * dt;

	_TotalVelocity.Set(_Velocity.x * 100, _Velocity.y * 100);

	//calculate remaining _Velocity x
	if (_Velocity.x != 0)
	{
		float remainingXVeloccity = _Velocity.x - 10 * _LinearDrag.x*abs(_Velocity.x) / _Velocity.x * dt;

		if (remainingXVeloccity*_Velocity.x <= 0)
		{
			_Velocity.Set(0, _Velocity.y);
		}
		else
		{
			_Velocity.Set(remainingXVeloccity, _Velocity.y);
		}
	}



	//calculate remaining _Velocity y
	float remainingYVelocity;

	if (_Velocity.y>=0)
	{
		remainingYVelocity = _Velocity.y - max(0, min(9.8, _LinearDrag.y)) * dt;
	}
	else
	{
		remainingYVelocity = _Velocity.y + max(0, min(9.8, _LinearDrag.y)) * dt;
	}


	_Velocity.Set(_Velocity.x, remainingYVelocity);



}

const Vector2& Body::GetTotalVelocity(float dt)
{
	
	return _TotalVelocity;
}

void Body::SetMass(float mass)
{
	_Mass = mass;
}

void Body::SetBodyType(BodyType type)
{
	_BodyType = type;
}

Body::BodyType Body::GetBodyType()
{
	return _BodyType;
}

float Body::GetMass() const
{
	return _Mass;
}
