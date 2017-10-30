#include "Body.h"

Body::Body()
{
	_Size.Set(0, 0);
	_Velocity.Set(0, 0);
	_Position.Set(0, 0);
	_Mass = 1;
}
Body::Body(float x, float y, float width, float height, float vx, float vy)
{
	_Size.Set(width, height);
	_Velocity.Set(vx, vy);
	_Position.Set(x, y);
	_Mass = 1;
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

Vector2 Body::GetVelocity()
{
	return _Velocity;
}
Vector2 Body::GetSize()
{
	return _Size;
}
Vector2 Body::GetPosition()
{
	return _Position;
}

void Body::Next(float dt)
{
	_Position.Set(_Position.x + _Velocity.x*dt, _Position.y + _Velocity.y*dt);
}

void Body::SetMass(float mass)
{
	_Mass = mass;
}

float Body::GetMass()
{
	return _Mass;
}