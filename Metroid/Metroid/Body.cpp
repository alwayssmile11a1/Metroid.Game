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
	_IsTrigger = false;
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
	_IsTrigger = false;
}
Body::~Body()
{

}

void Body::CalculateActualVelocity(float dt, float gravity)
{
	if (_BodyType == BodyType::Static || _IsTrigger)
	{
		_TotalVelocity.Set(0, 0);
		return;
	}

	//_Velocity.x = _Velocity.x * 100;
	_Velocity.y += _Mass * gravity * dt;

	//calculate remaining _Velocity x
	if (_Velocity.x != 0)
	{
		float remainingXVelocity = _Velocity.x - 10 * _LinearDrag.x*abs(_Velocity.x) / _Velocity.x * dt;

		if (remainingXVelocity*_Velocity.x <= 0)
		{
			_Velocity.Set(0, _Velocity.y);
		}
		else
		{
			_Velocity.Set(remainingXVelocity, _Velocity.y);
		}
	}

	//calculate remaining _Velocity y
	float remainingYVelocity;

	/*if (_Velocity.y > 0)
	{*/
		remainingYVelocity = _Velocity.y - _Velocity.y*_LinearDrag.y * dt;
	/*}
	else
	{
		if (_Velocity.y < 0)
		{
			remainingYVelocity = _Velocity.y + _Velocity.y*_LinearDrag.y * dt;
		}
	}*/

	if (remainingYVelocity*_Velocity.y < 0) remainingYVelocity = 0;

	//Set velocity (m/s)
	_Velocity.Set(_Velocity.x, remainingYVelocity);
	
	//Get actual velocity (cm/s)
	_TotalVelocity.Set(_Velocity.x * 100, _Velocity.y * 100);
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

void Body::SetID(const std::string &id)
{
	_ID = id;
}

const std::string& Body::GetID() const
{
	return _ID;
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

void Body::SetLinearDrag(float xDrag, float yDrag)
{
	if (xDrag < 0) xDrag = 0;
	if (yDrag < 0) yDrag = 0;
	_LinearDrag.Set(xDrag, yDrag);
}

void Body::Next(float dt, bool moveX, bool moveY)
{

	if (_BodyType == BodyType::Static || _IsTrigger)
	{
		return;
	}

	//Set body to the next position
	if (moveX)
	{
		_Position.Set(_Position.x + _TotalVelocity.x*dt, _Position.y);
	}

	if (moveY)
	{
		_Position.Set(_Position.x, _Position.y + _TotalVelocity.y*dt);

	}
	else
	{
		_Velocity.y = 0;
	}

}

const Vector2& Body::GetTotalVelocity() const
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

void  Body::IsTrigger(bool triggered)
{
	_IsTrigger = triggered;
}
bool Body::IsTrigger() const
{
	return _IsTrigger;
}