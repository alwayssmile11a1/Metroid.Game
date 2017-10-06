#include"Object.h"

#define FRAME_RATE 30
#define GROUND_Y 450

Object::Object()
{
	_Bounds = Vector2(0, 0);
	_Velocity = Vector2(0, 0);
	_Position = Vector2(0, 0);

}

Object::Object(float x, float y, float width, float height)
{
	_Bounds = Vector2(width, height);
	_Velocity = Vector2(0, 0);
	_Position = Vector2(x, y);
}

Object::Object(const Object &object)
{
	_Bounds = object._Bounds;
	_Velocity = object._Velocity;
	_Position = object._Position;
	_Sprite = object._Sprite;
}


Object::~Object()
{
	
}

Object& Object::operator=(const Object &object)
{
	_Bounds = object._Bounds;
	_Velocity = object._Velocity;
	_Position = object._Position;
	_Sprite = object._Sprite;
	return *this;
}

//All get functions
Vector2 Object::GetBounds()
{
	return _Bounds;
}

Vector2 Object::GetVelocity()
{
	return _Velocity;
}

Vector2 Object::GetPosition()
{
	return _Position;
}

Sprite Object::GetSprite()
{
	return _Sprite;
}

//All set functions
void Object::SetBounds(Vector2 value)
{
	_Bounds = value;
}
void Object::SetVelocity(Vector2 value)
{
	_Velocity = value;
}

void Object::SetPosition(Vector2 value)
{
	_Position = value;
}

void Object::SetSprite(Sprite sprite)
{
	_Sprite = sprite;
}

void Object::Update(DWORD dt)
{
	_Sprite.SetPosition(_Position.GetX(), _Position.GetY());

	_Sprite.Render();

}


