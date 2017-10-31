#include"Object.h"


Object::Object()
{
	
}

Object::Object(Texture *texture):Sprite(texture)
{

}

Object::Object(Texture *texture, float x, float y, float rectLeft, float rectTop, float rectWidth, float rectHeight)
	:Sprite(texture, x, y, rectLeft, rectTop, rectWidth, rectHeight)
{
	
}

//Object::Object(const Object &object)
//{
//	
//}


Object::~Object()
{
	
}

//Object& Object::operator=(const Object &object)
//{
//	
//	return *this;
//}

Body& Object::GetBody() 
{
	return _Body;
}

void  Object::SetBody(const Body &body)
{
	_Body = body;
}

void  Object::SetBodyPosition(float x, float y)
{
	_Body.SetPosition(x, y);
}
void  Object::SetVelocity(float vx, float vy)
{
	_Body.SetVelocity(vx, vy);
}
void  Object::SetBodySize(float width, float height)
{
	_Body.SetSize(width, height);
}

const Vector2& Object::GetVelocity() const
{
	return _Body.GetVelocity();
}

void Object::SetMass(float mass)
{
	_Body.SetMass(mass);
}


float Object::GetMass() const
{
	return _Body.GetMass();
}

void Object::Update(float dt)
{
	SetPosition(_Body.GetPosition().x, _Body.GetPosition().y);
}

void Object::FitBody()
{
	_Body.SetPosition(GetPosition().x, GetPosition().y);
	_Body.SetSize(GetSize().x, GetSize().y);
}
