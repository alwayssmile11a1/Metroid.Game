#include "Body.h"

Body::Body()
{
	_Size.Set(0, 0);
	_Velocity.Set(0, 0);
	_Position.Set(0, 0);
	_Mass = 1;
	_LinearImpulse.Set(0, 0);
	_TotalVelocity.Set(0, 0);
	_BodyType = BodyType::Static;
}
Body::Body(float x, float y, float width, float height, float vx, float vy)
{
	_Size.Set(width, height);
	_Velocity.Set(vx, vy);
	_Position.Set(x, y);
	_Mass = 1;
	_LinearImpulse.Set(0, 0);
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

void Body::Next(float dt)
{
	//Set body to the next position
	_Position.Set(_Position.x + GetTotalVelocity(dt).x*dt, _Position.y + GetTotalVelocity(dt).y*dt);


	//calculate remaining impulse
	if (_LinearImpulse.x != 0)
	{
		float remainingXImpulse = _LinearImpulse.x - abs(_LinearImpulse.x) / _LinearImpulse.x * dt/10;

		if (remainingXImpulse*_LinearImpulse.x <= 0)
		{
			_LinearImpulse.Set(0, _LinearImpulse.y);
		}
		else
		{
			_LinearImpulse.Set(remainingXImpulse, _LinearImpulse.y);
		}
	}

	if (_LinearImpulse.y != 0)
	{
		float remainingYImpulse = _LinearImpulse.y - abs(_LinearImpulse.y) / _LinearImpulse.y * dt/10;

		if (remainingYImpulse*_LinearImpulse.y <= 0)
		{
			_LinearImpulse.Set(_LinearImpulse.x, 0);
		}
		else
		{
			_LinearImpulse.Set(_LinearImpulse.x, remainingYImpulse);
		}
	}

	//_LinearImpulse.Set(0, 0);
}

const Vector2& Body::GetTotalVelocity(float dt)
{
	if (_BodyType == BodyType::Static)
	{
		_TotalVelocity.Set(0, 0);
		return _TotalVelocity;
	}

	//get the impulse accelerator
	float axImpulse = _LinearImpulse.x / _Mass;
	float ayImpulse = _LinearImpulse.y / _Mass;

	//get the total accelerator (m/millisecond^2)
	float ax = axImpulse / 1000;
	float ay = (ayImpulse - 9.8) / 1000;

	//Calculate the distances that this body can move in delta time span
	float dx = _Velocity.x / 10 * dt + 0.5 * ax * dt * dt;
	float dy = _Velocity.y / 10 * dt + 0.5 * ay * dt * dt; // s = Vo*t + 1/2*g*t^2;

	//Calculate total velocity
	float vx = dx / dt;
	float vy = dy / dt;

	_TotalVelocity.Set(vx, vy);

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

void  Body::ApplyLinearImpulse(float xImpulse, float yImpulse)
{
	//_LinearImpulse.Set(_LinearImpulse.x + xImpulse, _LinearImpulse.y + yImpulse);
	_LinearImpulse.Set(xImpulse, yImpulse);
}