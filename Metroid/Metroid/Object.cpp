#include"Object.h"

#define FRAME_RATE 30
#define GROUND_Y 450

Object::Object()
{
	_Bounds = Vector2(0, 0);
	_Velocity = Vector2(0, 0);
	_Position = Vector2(0, 0);
	_Texture = NULL;
}

Object::Object(float x, float y, float width, float height)
{
	_Bounds = Vector2(width, height);
	_Velocity = Vector2(0, 0);
	_Position = Vector2(x, y);
	_Texture = NULL;
}

Object::Object(const Object &object)
{
	_Bounds = object._Bounds;
	_Velocity = object._Velocity;
	_Position = object._Position;
	_Texture = object._Texture;

}


Object::~Object()
{
	//just for sure
	if (_Texture != NULL)
	{
		_Texture->~Texture();
		_Texture = NULL;
	}
}

Object& Object::operator=(const Object &object)
{
	_Bounds = object._Bounds;
	_Velocity = object._Velocity;
	_Position = object._Position;
	_Texture = object._Texture;
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

Texture* Object::GetTexture()
{
	return _Texture;
}

//All set functions
void Object::SetBounds(const Vector2 &value)
{
	_Bounds = value;
}
void Object::SetVelocity(const Vector2 &value)
{
	_Velocity = value;
}

void Object::SetPosition(const Vector2 &value)
{
	_Position = value;
}

void Object::SetTexture(Texture &texture)
{
	_Texture = &texture;
}

void Object::Update(DWORD dt)
{
	_Texture->Render(_Position.GetX(), _Position.GetY());
}


